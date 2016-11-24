//
//  clamp.hpp
//  Game Engine
//
//  Created by Indi Kernick on 12/09/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef clamp_hpp
#define clamp_hpp

#include <type_traits>

namespace Math {
  template <typename T>
  constexpr auto min(T a, T b) -> typename std::enable_if<std::is_arithmetic<T>::value, T>::type {
    return a < b ? a : b;
  }
  
  template <typename T>
  constexpr auto max(T a, T b) -> typename std::enable_if<std::is_arithmetic<T>::value, T>::type {
    return a > b ? a : b;
  }
  
  template <typename T>
  constexpr auto clamp(T value, T low, T high) -> typename std::enable_if<std::is_arithmetic<T>::value, T>::type {
    return value > low ? (value < high ? value : high) : low;
    //return min(max(value, low), high);
  }
  
  template <typename T>
  constexpr auto clampMin(T value, T low) -> typename std::enable_if<std::is_arithmetic<T>::value, T>::type {
    return value > low ? value : low;
  }
  
  template <typename T>
  constexpr auto clampMax(T value, T high) -> typename std::enable_if<std::is_arithmetic<T>::value, T>::type {
    return value < high ? value : high;
  }
}

#endif
