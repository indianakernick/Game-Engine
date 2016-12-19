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

namespace Math {
  /// n ^ 2
  template<typename T>
  constexpr auto square(T n) -> typename std::enable_if<std::is_arithmetic<T>::value, T>::type {
    return n*n;
  }
  /// n ^ 3
  template<typename T>
  constexpr auto cube(T n) -> typename std::enable_if<std::is_arithmetic<T>::value, T>::type {
    return n*n*n;
  }
  /// n ^ -2
  template<typename T>
  constexpr auto invSquare(T n) -> typename std::enable_if<std::is_arithmetic<T>::value, T>::type {
    return 1/(n*n);
  }
  /// n ^ -3
  template<typename T>
  constexpr auto invCube(T n) -> typename std::enable_if<std::is_arithmetic<T>::value, T>::type {
    return 1/(n*n*n);
  }
  
  template <int I>
  struct Pow {
    template <typename T>
    static constexpr auto calc(T val) -> typename std::enable_if<std::is_arithmetic<T>::value, T>::type {
      return val * Pow<I - 1>::calc(val);
    }
  };

  template <>
  struct Pow<1> {
    template <typename T>
    static constexpr auto calc(T val) -> typename std::enable_if<std::is_arithmetic<T>::value, T>::type {
      return val;
    }
  };

  template <>
  struct Pow<0> {
    template <typename T>
    static constexpr auto calc(T) -> typename std::enable_if<std::is_arithmetic<T>::value, T>::type {
      return 1;
    }
  };
  
  template <uint64_t NUM>
  struct Log2 {
    static const uint64_t value = 63 - __builtin_clz(NUM);
  };
  
  template <uint64_t NUM, uint64_t BASE, uint64_t NUM_DIV_BASE = NUM / BASE, uint64_t COUNT = 0>
  struct Log {
    static const uint64_t value = Log<NUM_DIV_BASE, BASE, NUM_DIV_BASE / BASE, COUNT + 1>::value;
  };

  template <uint64_t NUM, uint64_t BASE, uint64_t COUNT>
  struct Log<NUM, BASE, 0, COUNT> {
    static const uint64_t value = COUNT;
  };
}

#endif
