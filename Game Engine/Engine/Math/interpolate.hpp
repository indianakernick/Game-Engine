//
//  interpolate.hpp
//  game engine
//
//  Created by Indi Kernick on 4/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef interpolate_hpp
#define interpolate_hpp

#include <math.h>
#include "constants.hpp"

namespace Math {
  template<typename T>
  inline T lerp(double t, T from, T to) {
    return from + (to - from) * t;
  }
  ///Uses the -PId2 to 0 range of the sin function
  inline double sinIn(double t) {
    return 1 + sin(PId2 * t - PId2);
  }
  ///Uses the 0 to PId2 range of the sin function
  inline double sinOut(double t) {
    return sin(PId2 * t);
  }
  ///Uses the -PId2 to PId2 range of the sin function
  inline double sinInOut(double t) {
    return (1 + sin(PI * t - PId2)) / 2;
  }
  ///Uses the -2 to 0 range of the erf function
  inline double errorIn(double t) {
    return 1 + erf(2 * t - 2);
  }
  ///Uses the 0 to 2 range of the erf function
  inline double errorOut(double t) {
    return erf(2 * t);
  }
  ///Uses the -2 to 2 range of the erf function
  inline double errorInOut(double t) {
    return (1 + erf(4 * t - 2)) / 2;
  }
};

#endif