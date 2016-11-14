//
//  scale.hpp
//  game engine
//
//  Created by Indi Kernick on 12/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef scale_hpp
#define scale_hpp

namespace Math {
  ///Scales a value from one range to another
  template<typename T>
  inline T scale(T value, T fromMin, T fromMax, T toMin, T toMax) {
    return (value / (fromMax - fromMin) - fromMin) * (toMax - toMin) + toMin;
  }
  ///Scales a value from its range to a range of 0-1
  template<typename T>
  inline T fromRange(T value, T min, T max) {
    return (value - min) / (max - min);
  }
  ///Scales a value from a range of 0-1 to a new range
  template<typename T>
  inline T toRange(T value, T min, T max) {
    return value * (max - min) + min;
  }
}

#endif