//
//  event.cpp
//  Game Engine
//
//  Created by Indi Kernick on 11/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "event.hpp"

Event::Event()
  : time(Time::getI<std::chrono::milliseconds>()) {}

uint64_t Event::getTime() {
  return time;
}

void Event::setTime() {
  time = Time::getI<std::chrono::milliseconds>();
}
