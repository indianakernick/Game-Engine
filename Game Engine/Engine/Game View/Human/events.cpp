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

#define GET_TYPE(class) \
UI::Event::Type UI::class::getType() const { \
  return TYPE;\
}\

#define GET_NAME(class) \
const char *UI::class::getName() const { \
  return #class;\
}\

#define IMPL(class) \
DEFINE_TYPE(class) \
GET_TYPE(class) \
GET_NAME(class)

IMPL(MouseDown)
IMPL(MouseUp)
IMPL(MouseEnter)
IMPL(MouseLeave)
IMPL(MouseMove)

#undef IMPL
#undef GET_NAME
#undef GET_TYPE
#undef DEFINE_TYPE

UI::MouseUp::MouseUp(const bool within)
  : within(within) {}

UI::MouseEnter::MouseEnter(const bool down)
  : down(down) {}

UI::MouseLeave::MouseLeave(const bool down)
  : down(down) {}
