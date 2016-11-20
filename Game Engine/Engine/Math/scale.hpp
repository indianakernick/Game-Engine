//
//  scale.hpp
//  game engine
//
//  Created by Indi Kernick on 12/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef scale_hpp
#define scale_hpp

#include <type_traits>

namespace Math {
  ///Scales a value from one range to another
  template<typename T>
  inline auto scale(T value, T fromMin, T fromMax, T toMin, T toMax) -> typename std::enable_if<std::is_arithmetic<T>::value, T>::type {
    return (value / (fromMax - fromMin) - fromMin) * (toMax - toMin) + toMin;
  }
  ///Scales a value from its range to a range of 0-1
  template<typename T>
  inline auto fromRange(T value, T min, T max) -> typename std::enable_if<std::is_arithmetic<T>::value, T>::type {
    return (value - min) / (max - min);
  }
  ///Scales a value from a range of 0-1 to a new range
  template<typename T>
  inline auto toRange(T value, T min, T max) -> typename std::enable_if<std::is_arithmetic<T>::value, T>::type {
    return value * (max - min) + min;
  }
}

#endif
