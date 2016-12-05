//
//  mouse handler.cpp
//  Game Engine
//
//  Created by Indi Kernick on 4/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "mouse handler.hpp"

void Input::MouseHandler::captureOn() {
  assert(manager);
  manager->setMouseCapture(this);
}

void Input::MouseHandler::captureOff() {
  assert(manager);
  manager->setMouseCapture(nullptr);
}
