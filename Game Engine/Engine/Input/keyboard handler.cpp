//
//  keyboard handler.cpp
//  Game Engine
//
//  Created by Indi Kernick on 4/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "keyboard handler.hpp"

void Input::KeyboardHandler::focusOn() {
  assert(manager);
  manager->setKeyboardFocus(this);
}

void Input::KeyboardHandler::focusOff() {
  assert(manager);
  manager->setKeyboardFocus(nullptr);
}
