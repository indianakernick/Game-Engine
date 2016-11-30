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
    static auto calc(T val) -> typename std::enable_if<std::is_arithmetic<T>::value, T>::type {
      return val * Pow<I - 1>::calc(val);
    }
  };

  template <>
  struct Pow<1> {
    template <typename T>
    static auto calc(T val) -> typename std::enable_if<std::is_arithmetic<T>::value, T>::type {
      return val;
    }
  };

  template <>
  struct Pow<0> {
    template <typename T>
    static auto calc(T) -> typename std::enable_if<std::is_arithmetic<T>::value, T>::type {
      return 1;
    }
  };
}

#endif
