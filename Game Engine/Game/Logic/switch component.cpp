//
//  switch component.cpp
//  Game Engine
//
//  Created by Indi Kernick on 11/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "switch component.hpp"

Game::Switch::Switch() {
  onID = evtMan->addListener(Utils::memFunWrap(this, &Switch::onSwitchOn));
  offID = evtMan->addListener(Utils::memFunWrap(this, &Switch::onSwitchOff));
}

Game::Switch::~Switch() {
  evtMan->remListener(onID);
  evtMan->remListener(offID);
}

void Game::Switch::update(uint64_t) {
  setAllOutputs(state && anyInputOn());
}

void Game::Switch::onSwitchOn(const Events::SwitchOn::Ptr switchOn) {
  if (switchOn->pos == IDToPos(actor->getID())) {
    state = true;
  }
}

void Game::Switch::onSwitchOff(const Events::SwitchOff::Ptr switchOff) {
  if (switchOff->pos == IDToPos(actor->getID())) {
    state = false;
  }
}
