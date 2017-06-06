//
//  base.cpp
//  Game Engine
//
//  Created by Indi Kernick on 15/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "base.hpp"

void Game::Logic::update(uint64_t delta) {
  PROFILE(GameLogic update);

  updateActors(delta);
  processManager.update(delta);
}

void Game::Logic::quit() {
  PROFILE(GameLogic quit);

  processManager.killAll();
  //have to call update because the processes won't actually be killed until
  //update is called
  processManager.update(0);
  for (auto i = views.begin(); i != views.end(); ++i) {
    i->second->detach();
  }
  views.clear();
  actors.clear();
}

void Game::Logic::attachView(Game::View::Ptr view, Actor::ID actor) {
  View::ID id = idGen.make();
  view->attach(id, actor);
  views[id] = view;
}

void Game::Logic::detachView(Game::View::Ptr view) {
  view->detach();
  views.erase(view->getID());
}

Game::Actor::ID Game::Logic::createActor(const std::string &file) {
  const Actor::Ptr actor = factory.createActor(file);
  const Actor::ID id = actor->getID();
  actors[id] = actor;
  
  evtMan->emit(std::make_shared<Events::ActorCreated>(id));
  
  return id;
}

void Game::Logic::destroyActor(Actor::ID id) {
  auto iter = actors.find(id);
  if (iter != actors.end()) {
    actors.erase(iter);
    
    evtMan->emit(std::make_shared<Events::ActorDestroyed>(id));
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

Game::Logic::Views &Game::Logic::getViews() {
  return views;
}

void Game::Logic::updateActors(uint64_t delta) {
  for (auto i = actors.begin(); i != actors.end(); ++i) {
    i->second->update(delta);
  }
}
