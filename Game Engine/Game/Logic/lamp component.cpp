//
//  lamp component.cpp
//  Game Engine
//
//  Created by Indi Kernick on 11/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "lamp component.hpp"

Game::Events::LampOn::LampOn(const Actor::ID id)
  : lampID(id) {}

Game::Events::LampOff::LampOff(const Actor::ID id)
  : lampID(id) {}

void Game::Lamp::update(uint64_t) {
  setState(anyInputOn());
}

void Game::Lamp::setState(const bool newState) {
  if (newState != state) {
    if (newState) {
      evtMan->emit<Events::LampOn>(actor->getID());
    } else {
      evtMan->emit<Events::LampOff>(actor->getID());
    }
    state = newState;
  }
}
