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
    static_assert(1 < BASE && BASE <= SIZE_OF_CHAR_TABLE, "Unsupported base");
  
    Format() = delete;
    
    static const char *callU(uint64_t num) {
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
    
    static const char *callS(int64_t num) {
      static char out[PADDING + 2] = {0};
      uint8_t i = PADDING + 1;
      
      bool neg = false;
      if (num < 0) {
        neg = true;
        num = -num;
      }
      
      do {
        assert(i > 0 && "PADDING was too small for number");
        out[--i] = CHAR_TABLE[num % BASE];
      } while (num /= BASE);
      
      while (i != 1) {
        out[--i] = '0';
      }
      
      if (neg) {
        out[0] = '-';
        return out;
      } else {
        return out + 1;
      }
    }
  };
  
  template <uint8_t BASE>
  struct Format<BASE, 0> {
    static_assert(1 < BASE && BASE <= SIZE_OF_CHAR_TABLE, "Unsupported base");
  
    Format() = delete;
    
    static const char *callU(uint64_t num) {
      constexpr uint8_t WIDTH = log(BASE, std::numeric_limits<uint64_t>::max()) + 1;
      static char out[WIDTH + 1] = {0};
      uint8_t i = WIDTH;
      
      do {
        out[--i] = CHAR_TABLE[num % BASE];
      } while (num /= BASE);
      
      return out + i;
    }
    
    static const char *callS(int64_t num) {
      constexpr uint8_t WIDTH = log(BASE, std::numeric_limits<int64_t>::max()) + 2;
      static char out[WIDTH + 1] = {0};
      uint8_t i = WIDTH;
      
      bool neg = false;
      if (num < 0) {
        neg = true;
        num = -num;
      }
      
      do {
        out[--i] = CHAR_TABLE[num % BASE];
      } while (num /= BASE);
      
      if (neg) {
        out[--i] = '-';
      }
      
      return out + i;
    }
  };
  
  constexpr auto *decU = &Format<10>::callU;
  constexpr auto *binU = &Format<2>::callU;
  constexpr auto *octU = &Format<8>::callU;
  constexpr auto *hexU = &Format<16>::callU;
  
  constexpr auto *decS = &Format<10>::callS;
  constexpr auto *binS = &Format<2>::callS;
  constexpr auto *octS = &Format<8>::callS;
  constexpr auto *hexS = &Format<16>::callS;
  
  constexpr auto *binU8 = &Format<2, 8>::callU;
  constexpr auto *binU16 = &Format<2, 16>::callU;
  constexpr auto *binU32 = &Format<2, 32>::callU;
  constexpr auto *binU64 = &Format<2, 64>::callU;
  
  constexpr auto *binS8 = &Format<2, 8>::callS;
  constexpr auto *binS16 = &Format<2, 16>::callS;
  constexpr auto *binS32 = &Format<2, 32>::callS;
  constexpr auto *binS64 = &Format<2, 64>::callS;
  
  constexpr auto *hexU8 = &Format<16, 2>::callU;
  constexpr auto *hexU16 = &Format<16, 4>::callU;
  constexpr auto *hexU32 = &Format<16, 8>::callU;
  constexpr auto *hexU64 = &Format<16, 16>::callU;
  
  constexpr auto *hexS8 = &Format<16, 2>::callS;
  constexpr auto *hexS16 = &Format<16, 4>::callS;
  constexpr auto *hexS32 = &Format<16, 8>::callS;
  constexpr auto *hexS64 = &Format<16, 16>::callS;
}

#endif
