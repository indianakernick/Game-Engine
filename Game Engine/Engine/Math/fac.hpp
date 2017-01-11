//
//  fac.hpp
//  Game Engine
//
//  Created by Indi Kernick on 11/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_math_fac_hpp
#define engine_math_fac_hpp

#include <cstdint>
#include <type_traits>

namespace Math {
  template<typename T>
  inline constexpr auto fac(T num) -> typename std::enable_if<std::is_arithmetic<T>::value, T>::type {
    return num >= 0 ? num * fac(num - 1) : 1;
  }
  
  template <uint64_t N>
  struct Fac {
    static const uint64_t VALUE = N * Fac<N - 1>::VALUE;
  };
  
  template <>
  struct Fac<0> {
    static const uint64_t VALUE = 1;
  };
}

#endif
