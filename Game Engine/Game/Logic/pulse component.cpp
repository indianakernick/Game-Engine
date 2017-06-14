//
//  pulse component.cpp
//  Game Engine
//
//  Created by Indi Kernick on 11/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "pulse component.hpp"

Game::Pulse::Pulse()
  : durChangeID(evtMan->addListener(Utils::memFunWrap(this, &Pulse::onDurChange))) {}

Game::Pulse::~Pulse() {
  evtMan->remListener(durChangeID);
}

void Game::Pulse::update(uint64_t) {
  elapsed++;
  
  if (state) {
    if (elapsed >= onDuration) {
      state = false;
      elapsed = 0;
    }
  } else {
    if (elapsed >= offDuration) {
      state = true;
      elapsed = 0;
    }
  }
  
  setAllOutputs(state);
}

void Game::Pulse::onDurChange(const Events::PulseDurChange::Ptr durChange) {
  if (durChange->pos == IDToPos(actor->getID())) {
    onDuration = durChange->onDuration;
    offDuration = durChange->offDuration;
  }
}
