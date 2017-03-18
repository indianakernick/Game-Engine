//
//  event.cpp
//  Game Engine
//
//  Created by Indi Kernick on 11/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "event.hpp"

#define DEFINE_TYPE(class) \
const Game::Event::Type Input::class::TYPE = Game::EvtTypeGen::make();

#define GET_TYPE(class) \
Game::Event::Type Input::class::getType() const { \
  return TYPE;\
}\

#define GET_NAME(class) \
const char *Input::class::getName() const { \
  return #class;\
}\

#define IMPL(class) \
DEFINE_TYPE(class) \
GET_TYPE(class) \
GET_NAME(class)

IMPL(MouseDown)
IMPL(MouseUp)
IMPL(MouseMove)
IMPL(Scroll)
IMPL(KeyDown)
IMPL(KeyUp)
IMPL(WindowResize)
IMPL(Quit)

#undef IMPL
#undef GET_NAME
#undef GET_TYPE
#undef DEFINE_TYPE
