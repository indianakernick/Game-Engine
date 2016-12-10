//
//  keycode.cpp
//  Game Engine
//
//  Created by Indi Kernick on 4/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "keycode.hpp"

char Input::codeToChar(Key::Type key, Mod::Type modifiers) {
  static const char SHIFT_NUM_TABLE[] = {
    '!','@','#','$','%','^','&','*','(',')'
  };
  static const char SHIFT_SEMICOLON_TABLE[] = {
    ':','+','<','_','>','?','~'
  };
  static const char SEMICOLON_TABLE[] = {
    ';','=',',','-','.','/','`'
  };
  static const char SHIFT_LEFT_BRACKET_TABLE[] = {
    '{','|','}','"'
  };
  static const char LEFT_BRACKET_TABLE[] = {
    '[','\\',']','\''
  };
  
  bool capsLock = modifiers & Mod::CAPS_LOCK;
  bool shift = modifiers & Mod::SHIFT;
  
  using namespace Key;
  
  if (isAlpha(key)) {
    if (capsLock || shift) {
      return key;
    } else {
      return key + 32;
    }
  } else if (isNum(key)) {
    if (shift) {
      return SHIFT_NUM_TABLE[key - NUM_0];
    } else {
      return key;
    }
  } else if (key >= SEMICOLON && key <= BACK_QUOTE) {
    if (shift) {
      return SHIFT_SEMICOLON_TABLE[key - SEMICOLON];
    } else {
      return SEMICOLON_TABLE[key - SEMICOLON];
    }
  } else if (key >= LEFT_BRACKET && key <= QUOTE) {
    if (shift) {
      return SHIFT_LEFT_BRACKET_TABLE[key - LEFT_BRACKET];
    } else {
      return LEFT_BRACKET_TABLE[key - LEFT_BRACKET];
    }
  }
  
  return NOT_PRINTABLE;
}

uint8_t Input::getModifiers(const bool *keyStates) {
  return Mod::SHIFT      * keyStates[Key::SHIFT]     |
         Mod::CONTROL    * keyStates[Key::CONTROL]   |
         Mod::ALT        * keyStates[Key::ALT]       |
         Mod::CAPS_LOCK  * keyStates[Key::CAPS_LOCK] |
         Mod::LEFT_META  * keyStates[Key::LEFT_META] |
         Mod::RIGHT_META * keyStates[Key::RIGHT_META];
}

std::string Input::codeToWord(Key::Type key) {
  static const std::string ARROW[] = {
    "LEFT","UP","RIGHT","DOWN"
  };
  static const std::string NUM[] = {
    "0","1","2","3","4","5","6","7","8","9"
  };
  static const std::string ALPHA[] = {
    "A","B","C","D","E","F","G","H","I","J","K","L","M",
    "N","O","P","Q","R","S","T","U","V","W","X","Y","Z"
  };
  static const std::string FUNCTION[] = {
    "F1","F2","F3","F4", "F5", "F6",
    "F7","F8","F9","F10","F11","F12",
  };
  static const std::string SEMICOLON[] = {
    ":","=",",","-",".","/","`"
  };
  static const std::string LEFT_BRACKET[] = {
    "[","\\","]","'"
  };
  
  if (isArrow(key)) {
    return ARROW[key - Key::LEFT];
  } else if (isNum(key)) {
    return NUM[key - Key::NUM_0];
  } else if (isAlpha(key)) {
    return ALPHA[key - Key::A];
  } else if (isFunc(key)) {
    return FUNCTION[key - Key::F1];
  } else if (key >= Key::SEMICOLON && key <= Key::BACK_QUOTE) {
    return SEMICOLON[key - Key::SEMICOLON];
  } else if (key >= Key::LEFT_BRACKET && key <= Key::QUOTE) {
    return LEFT_BRACKET[key - Key::LEFT_BRACKET];
  } else {
    using namespace Key;
    switch (key) {
      case BACKSPACE:
        return "BACKSPACE";
      case TAB:
        return "TAB";
      case ENTER:
        return "ENTER";
      case SHIFT:
        return "SHIFT";
      case CONTROL:
        return "CONTROL";
      case ALT:
        return "ALT";
      case CAPS_LOCK:
        return "CAPS_LOCK";
      case ESCAPE:
        return "ESCAPE";
      case SPACE:
        return "SPACE";
      case LEFT_META:
        return "LEFT_META";
      case RIGHT_META:
        return "RIGHT_META";
    }
  }
  
  return "";
}

bool Input::isArrow(Key::Type key) {
  return key >= Key::LEFT && key <= Key::DOWN;
}

bool Input::isAlpha(Key::Type key) {
  return key >= Key::A && key <= Key::Z;
}

bool Input::isNum(Key::Type key) {
  return key >= Key::NUM_0 && key <= Key::NUM_9;
}

bool Input::isFunc(Key::Type key) {
  return key >= Key::F1 && key <= Key::F12;
}
