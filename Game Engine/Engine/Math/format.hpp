//
//  format.hpp
//  Game Engine
//
//  Created by Indi Kernick on 12/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef format_hpp
#define format_hpp

#include <cstdint>
#include <cstring>
#include <cassert>

namespace Math {
  namespace Format {
    template <uint8_t BASE>
    const char *any(uint64_t num) {
      static const char TABLE[36] = {
        '0','1','2','3','4','5','6','7','8','9',
        'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'
      };
      constexpr uint8_t WIDTH_TABLE[37] = {
        0,0,64,41,32,28,25,23,22,21,20,19,18,18,17,17,16,16,16,16,15,15,15,15,14,14,14,14,14,14,14,13,13,13,13,13,13
      };
      
      constexpr uint8_t WIDTH = WIDTH_TABLE[BASE];
      static char out[WIDTH + 1];
      out[WIDTH] = 0;
      uint8_t i = WIDTH;
      
      do {
        out[--i] = TABLE[num % BASE];
      } while (num /= BASE);
      return out + i;
    }
    
    template <>
    const char *any<1>(uint64_t num);
    
    template <>
    const char *any<0>(uint64_t num);
  
    const char *dec(uint64_t);
  
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
