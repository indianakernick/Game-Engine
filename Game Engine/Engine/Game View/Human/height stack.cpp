//
//  height stack.cpp
//  Game Engine
//
//  Created by Indi Kernick on 5/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "height stack.hpp"

UI::HeightStack::HeightStack()
  : OpStack(32, 0) {}

UI::Height UI::HeightStack::operation(const Height &prev, const Height &next) {
  return prev + next;
}
