//
//  case.hpp
//  game engine
//
//  Created by Indi Kernick on 9/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef case_hpp
#define case_hpp

#include <string>

namespace Strings {
  inline bool isLower(char c) {
    return c >= 'a' && c <= 'z';
  }
  inline bool isUpper(char c) {
    return c >= 'A' && c <= 'Z';
  }
  inline char toLower(char c) {
    return isUpper(c) ? c + 32 : c;
  }
  inline char toUpper(char c) {
    return isLower(c) ? c - 32 : c;
  }
  void toLower(char *string);
  void toUpper(char *string);
  void toLower(std::string &);
  void toUpper(std::string &);
}

#endif