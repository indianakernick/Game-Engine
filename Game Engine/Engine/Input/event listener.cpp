//
//  event listener.cpp
//  Game Engine
//
//  Created by Indi Kernick on 15/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "event listener.hpp"

#define DEFAULT_IMPL(event) bool Input::EventListener::on##event(const event *) {\
  return NOT_HANDLED;\
}

DEFAULT_IMPL(MouseDown)
DEFAULT_IMPL(MouseUp)
DEFAULT_IMPL(MouseMove)
DEFAULT_IMPL(Scroll)
DEFAULT_IMPL(KeyDown)
DEFAULT_IMPL(KeyUp)
DEFAULT_IMPL(WindowResize)
DEFAULT_IMPL(Quit)
