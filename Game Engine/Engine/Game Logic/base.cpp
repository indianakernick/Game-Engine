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
  const View::ID id = idGen.make();
  view->attach(id, actor);
  views[id] = view;
}

void Game::Logic::detachView(const Game::View::Ptr view) {
  view->detach();
  views.erase(view->getID());
}

Game::Actor::ID Game::Logic::createActor(const std::string &file) {
  const Actor::Ptr actor = factory.createActor(file);
  const Actor::ID id = actor->getID();
  createActorImpl(id, actor);
  
  evtMan->emit(std::make_shared<Events::ActorCreated>(id));
  
  return id;
}

void Game::Logic::destroyActor(const Actor::ID id) {
  if (destroyActorImpl(id)) {
    evtMan->emit(std::make_shared<Events::ActorDestroyed>(id));
  }
}

Game::ActorFactory &Game::Logic::getFactory() {
  return factory;
}

Game::Logic::Views &Game::Logic::getViews() {
  return views;
}
