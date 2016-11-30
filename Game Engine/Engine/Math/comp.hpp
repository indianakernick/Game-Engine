//
//  comp.hpp
//  Game Engine
//
//  Created by Indi Kernick on 6/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_math_comp_hpp
#define engine_math_comp_hpp

#include <math.h>

namespace Math {
  bool comp(float a, float b, float absEpsilon, float relEpsilon);
  bool comp(double a, double b, double absEpsilon, double relEpsilon);
  bool comp(long double a, long double b, long double absEpsilon, long double relEpsilon);
}

#endif
