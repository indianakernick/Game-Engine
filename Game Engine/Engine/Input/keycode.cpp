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
  
  if (key >= A && key <= Z) {
    if (capsLock || shift) {
      return key;
    } else {
      return key + 32;
    }
  } else if (key >= NUM_0 && key <= NUM_9) {
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
  return Mod::SHIFT     * keyStates[Key::SHIFT]     |
         Mod::CONTROL   * keyStates[Key::CONTROL]   |
         Mod::ALT       * keyStates[Key::ALT]       |
         Mod::CAPS_LOCK * keyStates[Key::CAPS_LOCK];
}
