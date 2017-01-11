//
//  base.cpp
//  Game Engine
//
//  Created by Indi Kernick on 15/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "base.hpp"

Game::Logic::Logic(EventManager::Ptr eventManager)
  : eventManager(eventManager) {}

void Game::Logic::update(uint64_t delta) {
  updateActors(delta);
}

void Game::Logic::attachView(Game::View::Ptr view, Actor::ID actor) {
  View::ID id = idGen.create();
  view->attach(id, actor);
  views[id] = view;
}

void Game::Logic::detachView(Game::View::Ptr view) {
  view->detach();
  views.erase(view->getID());
}

Game::Actor::ID Game::Logic::createActor(const Resource::ID &file) {
  Actor::Ptr actor = factory.createActor(file);
  Actor::ID id = actor->getID();
  actors[id] = actor;
  
  auto event = std::make_shared<Events::ActorCreated>(id);
  eventManager->trigger(event);
  
  return id;
}

void Game::Logic::destroyActor(Actor::ID id) {
  auto iter = actors.find(id);
  if (iter != actors.end()) {
    actors.erase(iter);
    
    auto event = std::make_shared<Events::ActorDestroyed>(id);
    eventManager->trigger(event);
  }
}

Game::Actor::Ptr Game::Logic::getActor(Actor::ID id) {
  auto iter = actors.find(id);
  if (iter != actors.end()) {
    return iter->second;
  } else {
    return nullptr;
  }
}

Game::ActorFactory &Game::Logic::getFactory() {
  return factory;
}

void Game::Logic::updateActors(uint64_t delta) {
  for (auto i = actors.begin(); i != actors.end(); ++i) {
    i->second->update(delta);
  }
}
