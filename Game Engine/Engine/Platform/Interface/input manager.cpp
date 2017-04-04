//
//  input manager.cpp
//  Game Engine
//
//  Created by Indi Kernick on 2/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "input manager.hpp"

using namespace Platform;

InputManager::InputManager(glm::ivec2 windowSize)
  : windowSize(windowSize) {}

void InputManager::update() {
  PROFILE(Input manager update);
  sendEvents();
}

void InputManager::sendEvent(Game::Event::Ptr event) {
  evtMan->emit(event);
}
