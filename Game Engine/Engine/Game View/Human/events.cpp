//
//  events.cpp
//  Game Engine
//
//  Created by Indi Kernick on 3/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "events.hpp"

#define DEFINE_TYPE(class) \
const UI::Event::Type UI::class::TYPE = UI::EventTypeGen::make();

DEFINE_TYPE(MouseDown)
DEFINE_TYPE(MouseUp)
DEFINE_TYPE(MouseEnter)
DEFINE_TYPE(MouseLeave)
DEFINE_TYPE(MouseMove)

#undef DEFINE_TYPE

UI::MouseUp::MouseUp(const bool within)
  : within(within) {}

UI::MouseEnter::MouseEnter(const bool down)
  : down(down) {}

UI::MouseLeave::MouseLeave(const bool down)
  : down(down) {}
