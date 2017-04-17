//
//  base.cpp
//  Game Engine
//
//  Created by Indi Kernick on 10/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "base.hpp"

Game::HumanView::HumanView() {}

void Game::HumanView::init() {
  PROFILE(HumanView init);
}

void Game::HumanView::update(uint64_t delta) {
  PROFILE(HumanView update);

  processManager.update(delta);
}

void Game::HumanView::render() {
  PROFILE(HumanView render);
}

void Game::HumanView::quit() {
  PROFILE(HumanView quit);
}

Game::View::Type Game::HumanView::getType() {
  return HUMAN;
}
