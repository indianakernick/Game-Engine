//
//  manager.cpp
//  Game Engine
//
//  Created by Indi Kernick on 4/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "manager.hpp"

void Input::Manager::addListener(EventListener::Ptr listener) {
  listeners.push_back(listener);
}

void Input::Manager::remListener(EventListener::Ptr listener) {
  listeners.remove(listener);
}

void Input::Manager::update(DeltaType) {
  //fill the queue
  update();
  
  //empty the queue
  while (!eventQueue.empty()) {
    Event::Ptr event = eventQueue.front();
    eventQueue.pop();
    
    for (auto i = listeners.begin(); i != listeners.end(); ++i) {
      if ((*i)->handleEvent(event)) {
        break;
      }
    }
  }
}

void Input::Manager::sendEvent(Event::Ptr event) {
  eventQueue.push(event);
}
