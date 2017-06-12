//
//  base.cpp
//  Game Engine
//
//  Created by Indi Kernick on 15/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "base.hpp"

void Game::Logic::init() {}

void Game::Logic::update(const uint64_t) {}

void Game::Logic::quit() {
  views.clear();
}

void Game::Logic::attachView(const Game::View::Ptr view, const Actor::ID actor) {
  const View::ID id = viewIDGen.make();
  view->attach(id, actor);
  views[id] = view;
}

void Game::Logic::detachView(const Game::View::Ptr view) {
  view->detach();
  views.erase(view->getID());
}

Game::Logic::Views &Game::Logic::getViews() {
  return views;
}

const Game::Logic::Views &Game::Logic::getViews() const {
  return views;
}

Game::ActorFactory &Game::Logic::getFactory() {
  return factory;
}

const Game::ActorFactory &Game::Logic::getFactory() const {
  return factory;
}
