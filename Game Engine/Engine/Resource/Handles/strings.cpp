//
//  strings.cpp
//  Game Engine
//
//  Created by Indi Kernick on 18/2/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "strings.hpp"

const std::wstring Res::Strings::EMPTY = L"";

const std::wstring &Res::Strings::get(const std::string &id) const {
  auto iter = strings.find(id);
  if (iter == strings.end()) {
    LOG_ERROR(UI,
      "String with ID \"%s\" not found in language \"%s\"",
      id.c_str(), language.c_str());
    return EMPTY;
  } else {
    return iter->second;
  }
}

std::string Res::Strings::getBytes(const std::string &id) const {
  static std::wstring_convert<std::codecvt_utf8<wchar_t>> strConv;
  
  auto iter = strings.find(id);
  if (iter == strings.end()) {
    LOG_ERROR(UI,
      "String with ID \"%s\" not found in language \"%s\"",
      id.c_str(), language.c_str());
    return "";
  } else {
    return strConv.to_bytes(iter->second);
  }
}

const std::string &Res::Strings::getLang() const {
  return language;
}
