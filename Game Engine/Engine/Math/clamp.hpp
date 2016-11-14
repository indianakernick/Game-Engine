//
//  clamp.hpp
//  Math
//
//  Created by Indi Kernick on 12/09/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef clamp_hpp
#define clamp_hpp

namespace Math {
  template <typename T>
  constexpr T min(T a, T b) {
    return a < b ? a : b;
  }
  
  template <typename T>
  constexpr T max(T a, T b) {
    return a > b ? a : b;
  }
  
  template <typename T>
  constexpr T clamp(T value, T low, T high) {
    return value > low ? (value < high ? value : high) : low;
    //return min(max(value, low), high);
  }
  
  template <typename T>
  constexpr T clampMin(T value, T low) {
    return value > low ? value : low;
  }
  
  template <typename T>
  constexpr T clampMax(T value, T high) {
    return value < high ? value : high;
  }
}

#endif