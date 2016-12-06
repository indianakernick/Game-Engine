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

namespace {
  //so that these aren't duplicated for every template instatiation
  const char CHAR_TABLE[36] {
    '0','1','2','3','4','5','6','7','8','9',
    'A','B','C','D','E','F','G','H','I','J',
    'K','L','M','N','O','P','Q','R','S','T',
    'U','V','W','X','Y','Z'
  };
  
  constexpr uint8_t WIDTH_TABLE[37] = {
    0,  0,  64, 41, 32, 28, 25, 23, 22, 21,
    20, 19, 18, 18, 17, 17, 16, 16, 16, 16,
    15, 15, 15, 15, 14, 14, 14, 14, 14, 14,
    14, 13, 13, 13, 13, 13, 13
  };
}

namespace Math {
  template <uint8_t BASE, uint8_t PADDING = 0>
  struct Format {
    Format() = delete;
    
    static const char *call(uint64_t num) {
      static_assert(BASE > 1 && BASE <= 36, "Unsupported base");
      
      static char out[PADDING + 1];
      memset(out, '0', PADDING);
      out[PADDING] = 0;
      uint8_t i = PADDING;
      
      do {
        assert(i > 0 && "PADDING was too small for number");
        out[--i] = CHAR_TABLE[num % BASE];
      } while (num /= BASE);
      return out;
    }
  };
  
  template <uint8_t BASE>
  struct Format<BASE, 0> {
    Format() = delete;
    
    static const char *call(uint64_t num) {
      static_assert(BASE > 1 && BASE <= 36, "Unsupported base");
      
      constexpr uint8_t WIDTH = WIDTH_TABLE[BASE];
      static char out[WIDTH + 1];
      out[WIDTH] = 0;
      uint8_t i = WIDTH;
      
      do {
        out[--i] = CHAR_TABLE[num % BASE];
      } while (num /= BASE);
      return out + i;
    }
  };
  
  using Dec = Format<10>;
  using Bin = Format<2>;
  using Oct = Format<8>;
  using Hex = Format<16>;
  
  using Bin8 = Format<2, 8>;
  using Bin16 = Format<2, 16>;
  using Bin32 = Format<2, 32>;
  using Bin64 = Format<2, 64>;
  
  using Hex8 = Format<16, 2>;
  using Hex16 = Format<16, 4>;
  using Hex32 = Format<16, 8>;
  using Hex64 = Format<16, 16>;
}

#endif
