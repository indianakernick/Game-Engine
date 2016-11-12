//
//  whitespace.hpp
//  game engine
//
//  Created by Indi Kernick on 1/09/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef whitespace_hpp
#define whitespace_hpp

namespace Strings {
  inline bool whitespace(char c) {
    switch (c) {
      case ' ':
      case '\t':
      case '\n':
        return true;
      default:
        return false;
    }
  }
}

#endif