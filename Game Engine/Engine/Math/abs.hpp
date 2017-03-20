//
//  abs.hpp
//  Game Engine
//
//  Created by Indi Kernick on 20/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_math_abs_hpp
#define engine_math_abs_hpp

#include <type_traits>

//it's about 50% faster than std::abs

namespace Math {
  template <typename T>
  constexpr std::enable_if_t<std::is_signed<T>::value, T>
  abs(const T num) {
    const std::make_unsigned_t<T> temp = num >> (sizeof(T) * 8 - 1);
    return (num ^ temp) + (temp & 1);
  }
  
  template <typename T>
  constexpr std::enable_if_t<std::is_unsigned<T>::value, T>
  abs(const T num) {
    return num;
  }
}

#endif
