//
//  pow.hpp
//  Game Engine
//
//  Created by Indi Kernick on 6/11/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_math_pow_hpp
#define engine_math_pow_hpp

#include <type_traits>
#include <cassert>

namespace Math {
  template <typename NUM, typename EXP>
  constexpr std::enable_if_t<std::is_arithmetic<NUM>::value &&
                             std::is_unsigned<EXP>::value, NUM>
  pow(NUM num, EXP exp) {
    NUM out = 1;
    while (exp--) {
      out *= num;
    }
    return out;
  }
  
  template <typename NUM, typename EXP>
  constexpr std::enable_if_t<std::is_arithmetic<NUM>::value &&
                             std::is_signed<EXP>::value, NUM>
  pow(NUM num, EXP exp) {
    if (exp < 0) {
      return 1 / pow(num, static_cast<std::make_unsigned_t<EXP>>(-exp));
    } else {
      return pow(num, static_cast<std::make_unsigned_t<EXP>>(exp));
    }
  }
  
  ///Compute the floor of the logarithm of a number
  constexpr uint64_t log(uint64_t base, uint64_t num) {
    assert(base > 1);
    assert(num != 0);
    
    uint64_t count = 0;
    while (num /= base) {
      ++count;
    }
    return count;
  }
  
  ///Compute the ceil of the logarithm of a number
  constexpr uint64_t logCeil(uint64_t base, uint64_t num) {
    assert(base > 1);
    assert(num != 0);
    
    uint64_t count = 0;
    bool up = false;
    while (uint64_t numDivBase = num / base) {
      up = up || (num % base);
      ++count;
      num = numDivBase;
    }
    return count + up;
  }
  
  ///Is num a power of base?
  constexpr bool isPower(uint64_t base, uint64_t num) {
    assert(base > 1);
    assert(num != 0);
    while (num % base == 0) {
      num /= base;
    }
    return num == 1;
  }
}

#endif
