//
//  comp.cpp
//  game engine
//
//  Created by Indi Kernick on 6/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "comp.hpp"

bool Math::comp(float a, float b, float absEpsilon, float relEpsilon) {
  float diff = fabsf(a - b);
  if (diff <= absEpsilon)
    return true;
  return diff <= ((fabsf(a) < fabsf(b) ? fabsf(b) : fabsf(a)) * relEpsilon);
}

bool Math::comp(double a, double b, double absEpsilon, double relEpsilon) {
  double diff = fabs(a - b);
  if (diff <= absEpsilon)
    return true;
  return diff <= ((fabs(a) < fabs(b) ? fabs(b) : fabs(a)) * relEpsilon);
}

bool Math::comp(long double a, long double b, long double absEpsilon, long double relEpsilon) {
  long double diff = fabsl(a - b);
  if (diff <= absEpsilon)
    return true;
  return diff <= ((fabsl(a) < fabsl(b) ? fabsl(b) : fabsl(a)) * relEpsilon);
}