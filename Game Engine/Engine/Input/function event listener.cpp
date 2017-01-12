//
//  function event listener.cpp
//  Game Engine
//
//  Created by Indi Kernick on 12/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "function event listener.hpp"

Input::FunctionEventListener::FunctionEventListener(bool cast)
  : EventListener(cast) {}

#define SETTER(event, eventLowercase) void Input::FunctionEventListener::set##event##Func(const std::function<void (event::Ptr)> &func) {\
  eventLowercase##Func = func;\
}

SETTER(Event, event)
SETTER(MouseDown, mouseDown)
SETTER(MouseUp, mouseUp)
SETTER(MouseMove, mouseMove)
SETTER(Scroll, scroll)
SETTER(KeyDown, keyDown)
SETTER(KeyUp, keyUp)
SETTER(WindowResize, windowResize)
SETTER(Quit, quit)

#define ON(event, eventLowercase) bool Input::FunctionEventListener::on##event(event::Ptr e) {\
  if (eventLowercase##Func) {\
    eventLowercase##Func(e);\
    return HANDLED;\
  } else {\
    return NOT_HANDLED;\
  }\
}

ON(Event, event)
ON(MouseDown, mouseDown)
ON(MouseUp, mouseUp)
ON(MouseMove, mouseMove)
ON(Scroll, scroll)
ON(KeyDown, keyDown)
ON(KeyUp, keyUp)
ON(WindowResize, windowResize)
ON(Quit, quit)
