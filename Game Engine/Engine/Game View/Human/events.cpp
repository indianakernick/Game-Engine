//
//  events.cpp
//  Game Engine
//
//  Created by Indi Kernick on 3/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "events.hpp"

UI::MouseUp::MouseUp(const bool within)
  : within(within) {}

UI::MouseEnter::MouseEnter(const bool down)
  : down(down) {}

UI::MouseLeave::MouseLeave(const bool down)
  : down(down) {}
