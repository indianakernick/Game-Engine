//
//  format.hpp
//  game engine
//
//  Created by Indi Kernick on 12/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef format_hpp
#define format_hpp

#include <cstdint>

namespace Math {
  namespace Format {
    const char *bin(uint64_t);
    const char *oct(uint64_t);
    const char *hex(uint64_t);
    
    const char *binPad64(uint64_t);
    const char *octPad64(uint64_t);
    const char *hexPad64(uint64_t);
    
    const char *binPad32(uint32_t);
    const char *octPad32(uint32_t);
    const char *hexPad32(uint32_t);
    
    const char *binPad16(uint16_t);
    const char *octPad16(uint16_t);
    const char *hexPad16(uint16_t);
    
    const char *binPad8(uint8_t);
    const char *octPad8(uint8_t);
    const char *hexPad8(uint8_t);
  }
}

#endif