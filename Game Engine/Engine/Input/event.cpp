//
//  event.cpp
//  Game Engine
//
//  Created by Indi Kernick on 11/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "event.hpp"

#define DEFINE_TYPE(class, enum) const Input::Type Input::class::TYPE = Input::enum;

DEFINE_TYPE(MouseDown, MOUSE_DOWN)
DEFINE_TYPE(MouseUp, MOUSE_UP)
DEFINE_TYPE(MouseMove, MOUSE_MOVE)
DEFINE_TYPE(Scroll, SCROLL)
DEFINE_TYPE(KeyDown, KEY_DOWN)
DEFINE_TYPE(KeyUp, KEY_UP)
DEFINE_TYPE(WindowResize, WINDOW_RESIZE)
DEFINE_TYPE(Quit, QUIT)

#define GET_TYPE(class) Input::Type Input::class::getType() const {\
  return TYPE;\
}

GET_TYPE(MouseDown)
GET_TYPE(MouseUp)
GET_TYPE(MouseMove)
GET_TYPE(Scroll)
GET_TYPE(KeyDown)
GET_TYPE(KeyUp)
GET_TYPE(WindowResize)
GET_TYPE(Quit)
