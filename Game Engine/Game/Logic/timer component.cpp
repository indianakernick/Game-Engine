//
//  timer component.cpp
//  Game Engine
//
//  Created by Indi Kernick on 11/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "timer component.hpp"

Game::Timer::Timer()
  : durChangeID(evtMan->addListener(Utils::memFunWrap(this, &Timer::onDurChange))) {}

Game::Timer::~Timer() {
  evtMan->remListener(durChangeID);
}

void Game::Timer::update(uint64_t) {
  flow.push(anyInputOn());
  setAllOutputs(flow.front());
  flow.pop();
}

void Game::Timer::onDurChange(const Events::TimerDurChange::Ptr durChange) {
  if (durChange->pos == IDToPos(actor->getID()) && durChange->duration != duration) {
    duration = durChange->duration;
    while (flow.size() < duration) {
      flow.push(false);
    }
    while (flow.size() > duration) {
      flow.pop();
    }
  }
}
