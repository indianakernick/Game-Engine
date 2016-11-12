//
//  alphabetchar.hpp
//  game engine
//
//  Created by Indi Kernick on 16/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef alphabetchar_hpp
#define alphabetchar_hpp

namespace Strings {
  inline bool alphabet(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
  }
}

#endif