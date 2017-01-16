//
//  human.cpp
//  Game Engine
//
//  Created by Indi Kernick on 10/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "human.hpp"

Game::HumanView::HumanView()
  : limiter(16) {}

void Game::HumanView::init() {
  root->init();
}

void Game::HumanView::update(uint64_t delta) {
  root->input();
  root->update(delta);
}

void Game::HumanView::render() {
  if (limitRenderFreq && !limiter.canDo()) {
    return;
  }
  root->render();
}

Game::View::Type Game::HumanView::getType() {
  return HUMAN;
}

RootElement::Ptr Game::HumanView::getRoot() {
  return root;
}

bool Game::HumanView::onEvent(const Input::Event::Ptr event) {
  return root->input(event);
}
