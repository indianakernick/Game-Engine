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

#define ACCEPT(class) bool Input::class::accept(EventListener *listener) const {\
  return listener->on##class(this);\
}

ACCEPT(MouseDown)
ACCEPT(MouseUp)
ACCEPT(MouseMove)
ACCEPT(Scroll)
ACCEPT(KeyDown)
ACCEPT(KeyUp)
ACCEPT(WindowResize)
ACCEPT(Quit)
