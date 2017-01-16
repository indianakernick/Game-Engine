//
//  function event listener.cpp
//  Game Engine
//
//  Created by Indi Kernick on 12/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "function event listener.hpp"

#define SETTER(event, eventLowercase) void Input::FunctionEventListener::set##event##Func(const std::function<bool (const event *)> &func) {\
  eventLowercase##Func = func;\
}

SETTER(MouseDown, mouseDown)
SETTER(MouseUp, mouseUp)
SETTER(MouseMove, mouseMove)
SETTER(Scroll, scroll)
SETTER(KeyDown, keyDown)
SETTER(KeyUp, keyUp)
SETTER(WindowResize, windowResize)
SETTER(Quit, quit)

#define ON(event, eventLowercase) bool Input::FunctionEventListener::on##event(const event *e) {\
  if (eventLowercase##Func) {\
    return eventLowercase##Func(e);\
  } else {\
    return NOT_HANDLED;\
  }\
}

ON(MouseDown, mouseDown)
ON(MouseUp, mouseUp)
ON(MouseMove, mouseMove)
ON(Scroll, scroll)
ON(KeyDown, keyDown)
ON(KeyUp, keyUp)
ON(WindowResize, windowResize)
ON(Quit, quit)
