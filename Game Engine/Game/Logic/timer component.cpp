//
//  timer component.cpp
//  Game Engine
//
//  Created by Indi Kernick on 11/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "timer component.hpp"

Game::Events::TimerDurChange::TimerDurChange(const Actor::ID id, const uint32_t duration)
  : timerID(id), newDuration(duration) {}

Game::Timer::Timer() {
  durChangeID = evtMan->addListener(Utils::memFunWrap(this, &Timer::onDurChange));
}

Game::Timer::~Timer() {
  evtMan->remListener(durChangeID);
}

void Game::Timer::update(uint64_t) {
  flow.push(anyInputOn());
  setAllOutputs(flow.front());
  flow.pop();
}

void Game::Timer::onDurChange(const Events::TimerDurChange::Ptr durChange) {
  if (durChange->timerID == actor->getID() && durChange->newDuration != duration) {
    duration = durChange->newDuration;
    while (flow.size() < duration) {
      flow.push(false);
    }
    while (flow.size() > duration) {
      flow.pop();
    }
  }
}
