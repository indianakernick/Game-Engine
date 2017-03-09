//
//  pow.hpp
//  Math
//
//  Created by Indi Kernick on 6/11/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_math_pow_hpp
#define engine_math_pow_hpp

#include <type_traits>
#include <cassert>

namespace Math {
  template <typename T>
  constexpr std::enable_if_t<std::is_arithmetic<T>::value, T>
  pow(T num, int64_t exp) {
    if (exp > 0) {
      return num * pow(num, exp - 1);
    } else if (exp == 0) {
      return static_cast<T>(1);
    } else {//exp < 0
      return static_cast<T>(1) / pow(num, -exp);
    }
  }
  
  constexpr uint64_t log(uint64_t base, uint64_t num, uint64_t count = 0) {
    assert(num != 0);
    const uint64_t numDivBase = num / base;
    return numDivBase == 0 ? count : log(base, numDivBase, count + 1);
  }
  
  constexpr uint64_t logCeil(uint64_t base, uint64_t num) {
    const uint64_t logVal = log(base, num);
    return pow(base, logVal) == num ? logVal : logVal + 1;
  }
  
  constexpr bool isPowerOf(uint64_t base, uint64_t num) {
    return pow(base, log(base, num)) == num;
  }
  
  constexpr uint64_t nextPowerOf(uint64_t base, uint64_t num) {
    return pow(base, log(base, num));
  }
}

#endif
