//
//  fac.hpp
//  game engine
//
//  Created by Indi Kernick on 11/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef fac_hpp
#define fac_hpp

#include <stdint.h>
#include <type_traits>

namespace Math {
  template<typename T>
  inline constexpr auto fac(T num) -> typename std::enable_if<std::is_arithmetic<T>::value, T>::type {
    return num ? num * fac(num - 1) : 1;
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
