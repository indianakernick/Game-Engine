//
//  strings.cpp
//  Game Engine
//
//  Created by Indi Kernick on 18/2/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "strings.hpp"

Res::StringsParseError::StringsParseError(std::string what)
  : std::runtime_error(what) {}

const std::string &Res::StringsLoader::getName() const {
  static const std::string NAME = "Strings";
  return NAME;
}

bool Res::StringsLoader::canLoad(std::experimental::string_view ext) const {
  return ext == "strings";
}

//some sequences of characters
const char BEG_COM[2] = {'/','*'};
const char END_COM[2] = {'*','/'};
const char BEG_STR[1] = {'\"'};
const char END_STR[1] = {'\"'};
const char SEP[1]     = {'='};
const char TERM[1]    = {';'};

//the next sequence index
int nextSeqIndex = 0;

template <size_t SIZE>
bool find(char c, const char (&str)[SIZE], bool &maybe) {
  constexpr int INT_SIZE = static_cast<int>(SIZE);
  
  if (nextSeqIndex >= INT_SIZE) {
    return false;
  }
  if (c == str[nextSeqIndex]) {
    if (nextSeqIndex == INT_SIZE - 1) {
      nextSeqIndex = 0;
      return true;
    } else {
      nextSeqIndex++;
      maybe = true;
    }
  }
  return false;
}

template <>
bool find<1>(char c, const char(&str)[1], bool &) {
  return nextSeqIndex == 0 && c == str[0];
}

template <size_t SIZE>
bool findOnly(char c, const char (&str)[SIZE], bool &maybe) {
  constexpr int INT_SIZE = static_cast<int>(SIZE);
  
  if (nextSeqIndex >= INT_SIZE) {
    nextSeqIndex = 0;
  }
  if (c == str[nextSeqIndex]) {
    if (nextSeqIndex == INT_SIZE - 1) {
      nextSeqIndex = 0;
      return true;
    } else {
      nextSeqIndex++;
      maybe = true;
    }
  } else {
    nextSeqIndex = 0;
  }
  return false;
}

template <>
bool findOnly<1>(char c, const char (&str)[1], bool &) {
  nextSeqIndex = 0;
  return c == str[0];
}

Res::Handle::Ptr Res::StringsLoader::load(const Res::ID &id) const {
  Res::Strings::Ptr strings = std::make_shared<Res::Strings>();
  const Memory::Buffer file = readFile(id);
  LineCol lineCol;
  State state = WHITE_SPACE;
  std::string key;
  std::string val;
 
  strings->language = id.getName().to_string();
  nextSeqIndex = 0;
  
  for (const char *c = file.cbegin<char>(); c < file.cend<char>(); c++) {
    try {
      handleState(state, *c, key, val, strings);
    } catch (StringsParseError &e) {
      LOG_ERROR(RESOURCES, "Strings - %s %s", lineCol.asStr(), e.what());
    }
    lineCol.update(*c);
  }
  
  return strings;
}

void Res::StringsLoader::changeState(State &state, State newState) {
  if (newState != NO_CHANGE) {
    state = newState;
  }
}

void Res::StringsLoader::handleState(
  State &state,
  char c,
  std::string &key,
  std::string &val,
  Strings::Ptr strings
) {
  switch (state) {
    case WHITE_SPACE:
      changeState(state, whiteSpace(c));
      break;
    case COMMENT:
      changeState(state, comment(c));
      break;
    case KEY_STR:
      changeState(state, keyStr(c, key));
      break;
    case AFTER_KEY_STR:
      changeState(state, afterKeyStr(c));
      break;
    case BEFORE_VAL_STR:
      changeState(state, beforeValStr(c));
      break;
    case VAL_STR:
      changeState(state, valStr(c, val));
      break;
    case AFTER_VAL_STR:
      changeState(state, afterValStr(c, key, val, strings));
      break;
    
    default:
      assert(false);
  }
}

Res::StringsLoader::State Res::StringsLoader::whiteSpace(char c) {
  if (!std::isspace(c)) {
    bool maybe = false;
    if (find(c, BEG_COM, maybe)) {
      return COMMENT;
    } else if (find(c, BEG_STR, maybe)) {
      return KEY_STR;
    } else if (!maybe) {
      throw StringsParseError("Invalid char");
    }
  }
  return NO_CHANGE;
}

Res::StringsLoader::State Res::StringsLoader::comment(char c) {
  //maybe isnt used
  bool maybe = false;
  if (findOnly(c, END_COM, maybe)) {
    return WHITE_SPACE;
  }
  return NO_CHANGE;
}

Res::StringsLoader::State Res::StringsLoader::keyStr(char c, std::string &key) {
  //maybe isnt used
  bool maybe = false;
  if (findOnly(c, END_STR, maybe)) {
    return AFTER_KEY_STR;
  } else if (c == '\n') {
    throw StringsParseError("Key must be single line");
  } else {
    key += c;
  }
  return NO_CHANGE;
}

Res::StringsLoader::State Res::StringsLoader::afterKeyStr(char c) {
  bool maybe = false;
  if (findOnly(c, SEP, maybe)) {
    return BEFORE_VAL_STR;
  } else if (!std::isspace(c) && !maybe) {
    throw StringsParseError("Invalid char after key");
  }
  return NO_CHANGE;
}

Res::StringsLoader::State Res::StringsLoader::beforeValStr(char c) {
  bool maybe = false;
  if (findOnly(c, BEG_STR, maybe)) {
    return VAL_STR;
  } else if (!std::isspace(c) && !maybe) {
    throw StringsParseError("Invalid char before val");
  }
  return NO_CHANGE;
}

Res::StringsLoader::State Res::StringsLoader::valStr(char c, std::string &val) {
  //maybe isnt used
  bool maybe = false;
  if (findOnly(c, END_STR, maybe)) {
    return AFTER_VAL_STR;
  } else if (c == '\n') {
    throw StringsParseError("Val must be single line");
  } else {
    val += c;
  }
  return NO_CHANGE;
}

Res::StringsLoader::State Res::StringsLoader::afterValStr(
  char c,
  std::string &key,
  std::string &val,
  Strings::Ptr strings
) {
  static std::wstring_convert<std::codecvt_utf8<wchar_t>> strConv;

  bool maybe = false;
  if (findOnly(c, TERM, maybe)) {
    //the key is ascii and the val is utf-8
    const std::wstring wval = strConv.from_bytes(val);
    strings->strings.emplace(key, wval);
    strings->addSize(key.size() + wval.size() * sizeof(wchar_t));
    key.clear();
    val.clear();
    return WHITE_SPACE;
  } else if (!std::isspace(c) && !maybe) {
    throw StringsParseError("Invalid char after val");
  }
  return NO_CHANGE;
}
