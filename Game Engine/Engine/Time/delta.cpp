//
//  delta.cpp
//  Game Engine
//
//  Created by Indi Kernick on 22/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "delta.hpp"

Time::Delta::Delta(Unit unit)
  : unit(unit), lastTime(getF(unit)) {}

double Time::Delta::get() {
  double time = getF(unit);
  double delta = time - lastTime;
  lastTime = time;
  return delta;
}
