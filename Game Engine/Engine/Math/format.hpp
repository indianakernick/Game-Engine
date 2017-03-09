//
//  format.hpp
//  Game Engine
//
//  Created by Indi Kernick on 12/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_math_format_hpp
#define engine_math_format_hpp

#include <cstdint>
#include <cstring>
#include <cassert>
#include <string>
#include "pow.hpp"

namespace Math {
  //so that these aren't duplicated for every template instatiation
  constexpr char CHAR_TABLE[36] {
    '0','1','2','3','4','5','6','7','8','9',
    'A','B','C','D','E','F','G','H','I','J',
    'K','L','M','N','O','P','Q','R','S','T',
    'U','V','W','X','Y','Z'
  };

  constexpr size_t SIZE_OF_CHAR_TABLE = std::extent<decltype(CHAR_TABLE)>::value;

  template <uint8_t BASE, uint8_t PADDING = 0>
  struct Format {
    Format() = delete;
    
    static const char *call(uint64_t num) {
      static_assert(1 < BASE && BASE <= SIZE_OF_CHAR_TABLE, "Unsupported base");
      
      static char out[PADDING + 1] = {0};
      uint8_t i = PADDING;
      
      do {
        assert(i > 0 && "PADDING was too small for number");
        out[--i] = CHAR_TABLE[num % BASE];
      } while (num /= BASE);
      
      while (i != 0) {
        out[--i] = '0';
      }
      
      return out;
    }
  };
  
  template <uint8_t BASE>
  struct Format<BASE, 0> {
    Format() = delete;
    
    static const char *call(uint64_t num) {
      static_assert(1 < BASE && BASE <= SIZE_OF_CHAR_TABLE, "Unsupported base");
      
      constexpr uint8_t WIDTH = log(BASE, std::numeric_limits<uint64_t>::max()) + 1;
      static char out[WIDTH + 1] = {0};
      uint8_t i = WIDTH;
      
      do {
        out[--i] = CHAR_TABLE[num % BASE];
      } while (num /= BASE);
      
      return out + i;
    }
  };
  
  constexpr auto *dec = &Format<10>::call;
  constexpr auto *bin = &Format<2>::call;
  constexpr auto *oct = &Format<8>::call;
  constexpr auto *hex = &Format<16>::call;
  
  constexpr auto *bin8 = &Format<2, 8>::call;
  constexpr auto *bin16 = &Format<2, 16>::call;
  constexpr auto *bin32 = &Format<2, 32>::call;
  constexpr auto *bin64 = &Format<2, 64>::call;
  
  constexpr auto *hex8 = &Format<16, 2>::call;
  constexpr auto *hex16 = &Format<16, 4>::call;
  constexpr auto *hex32 = &Format<16, 8>::call;
  constexpr auto *hex64 = &Format<16, 16>::call;
}

#endif
