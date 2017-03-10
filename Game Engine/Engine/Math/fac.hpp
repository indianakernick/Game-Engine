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
  constexpr std::enable_if_t<std::is_arithmetic<T>::value, T>
  fac(T num) {
    return num > 1 ? num * fac(num - 1) : 1;
  }
}

#endif
