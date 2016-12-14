//
//  mouse.cpp
//  Game Engine
//
//  Created by Indi Kernick on 4/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "mouse.hpp"

void Input::Handlers::Mouse::captureOn() {
  assert(manager);
  manager->setMouseCapture(this);
}

void Input::Handlers::Mouse::captureOff() {
  assert(manager);
  manager->setMouseCapture(nullptr);
}
