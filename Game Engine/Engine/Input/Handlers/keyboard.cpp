//
//  keyboard.cpp
//  Game Engine
//
//  Created by Indi Kernick on 4/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "keyboard.hpp"

void Input::Handlers::Keyboard::focusOn() {
  assert(manager);
  manager->setKeyboardFocus(this);
}

void Input::Handlers::Keyboard::focusOff() {
  assert(manager);
  manager->setKeyboardFocus(nullptr);
}
