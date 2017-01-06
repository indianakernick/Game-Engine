//
//  manager.cpp
//  Game Engine
//
//  Created by Indi Kernick on 4/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "manager.hpp"

Input::Manager::Manager(Geometry::Size windowSize)
  : windowSize(windowSize) {}

void Input::Manager::addListener(EventListener::Ptr listener) {
  listeners.push_back(listener);
}

void Input::Manager::remListener(EventListener::Ptr listener) {
  listeners.remove(listener);
}

void Input::Manager::addQuitListener(QuitListener listener) {
  quitListeners.push_back(listener);
}

void Input::Manager::remQuitListener(QuitListener listener) {
  quitListeners.remove_if([&listener](QuitListener other) {
    return listener.target<QuitListener>() == other.target<QuitListener>();
  });
}

void Input::Manager::update() {
  //fill the queue
  sendEvents();
  
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

void Input::Manager::quitEvent(Quit::Ptr event) {
  eventQueue.push(event);
  for (auto i = quitListeners.begin(); i != quitListeners.end(); ++i) {
    (*i)();
  }
}
