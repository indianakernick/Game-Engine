//
//  comp.hpp
//  Game Engine
//
//  Created by Indi Kernick on 6/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_math_comp_hpp
#define engine_math_comp_hpp

#include <cmath>
#include <limits>

namespace Math {
  template <typename T>
  auto comp(T a, T b, T epsilon = std::numeric_limits<T>::epsilon())
    -> typename std::enable_if<std::is_floating_point<T>::value, bool>::type {
    return std::abs(a - b) < epsilon;
  }
}

#endif
