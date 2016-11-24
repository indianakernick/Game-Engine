//
//  digitchar.hpp
//  Game Engine
//
//  Created by Indi Kernick on 1/09/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef digitchar_hpp
#define digitchar_hpp

namespace Strings {
  inline bool intChar(char c) {
    return c == '-' || (c >= '0' && c <= '9');
  }
  inline bool floatChar(char c) {
    return intChar(c) || c == '.' || c == '+' || c == 'e' || c == 'E';
  }
}

#endif
