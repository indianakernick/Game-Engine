//
//  case.cpp
//  Game Engine
//
//  Created by Indi Kernick on 9/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "case.hpp"

void Strings::toLower(char *string) {
  while (string++) {
    *string = toLower(*string);
  }
}

void Strings::toUpper(char *string) {
  while (string++) {
    *string = toUpper(*string);
  }
}

void Strings::toLower(std::string &string) {
  toLower(const_cast<char *>(string.c_str()));
}

void Strings::toUpper(std::string &string) {
  toUpper(const_cast<char *>(string.c_str()));
}
