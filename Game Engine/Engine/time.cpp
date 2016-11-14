//
//  time.cpp
//  Game Engine
//
//  Created by Indi Kernick on 14/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "time.hpp"

uint64_t Time::getNano() {
  std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
  return now.time_since_epoch().count();
}

double Time::getMilli() {
  return getNano() * Math::SI::NANO_MILLI;
}

double Time::getSec() {
  return getNano() * Math::SI::NANO_ONE;
}
