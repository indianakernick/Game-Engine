//
//  event element.cpp
//  Game Engine
//
//  Created by Indi Kernick on 13/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "event element.hpp"

void EventElement::pushEvent(Events::Event::Ptr event) {
  eventQueue.push(event);
}

void EventElement::dispatchEvents() {
  while (!eventQueue.empty()) {
    eventQueue.front()->accept(this);
    eventQueue.pop();
  }
}
