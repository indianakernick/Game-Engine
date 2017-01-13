//
//  event listener.cpp
//  Game Engine
//
//  Created by Indi Kernick on 15/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "event listener.hpp"

Input::EventListener::EventListener(bool cast)
  : cast(cast) {}

#define DOWN_CAST(eventType) return on##eventType(std::dynamic_pointer_cast<eventType>(event));

bool Input::EventListener::handleEvent(Input::Event::Ptr event) {
  if (cast) {
    switch (event->getType()) {
      case MOUSE_DOWN:
        DOWN_CAST(MouseDown)
      case MOUSE_UP:
        DOWN_CAST(MouseUp)
      case MOUSE_MOVE:
        DOWN_CAST(MouseMove)
      case SCROLL:
        DOWN_CAST(Scroll)
      case KEY_DOWN:
        DOWN_CAST(KeyDown)
      case KEY_UP:
        DOWN_CAST(KeyUp)
      case WINDOW_RESIZE:
        DOWN_CAST(WindowResize)
      case QUIT:
        DOWN_CAST(Quit)
    }
  } else {
    return onEvent(event);
  }
}

#define DEFAULT_IMPL(event) bool Input::EventListener::on##event(event::Ptr) {\
  return NOT_HANDLED;\
}

DEFAULT_IMPL(Event)
DEFAULT_IMPL(MouseDown)
DEFAULT_IMPL(MouseUp)
DEFAULT_IMPL(MouseMove)
DEFAULT_IMPL(Scroll)
DEFAULT_IMPL(KeyDown)
DEFAULT_IMPL(KeyUp)
DEFAULT_IMPL(WindowResize)
DEFAULT_IMPL(Quit)
