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

void Input::Manager::update() {
  PROFILE(Input manager update);
  sendEvents();
}

void Input::Manager::sendEvent(Game::Event::Ptr event) {
  evtMan->emit(event);
}
