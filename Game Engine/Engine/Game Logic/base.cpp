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

ID::Type Game::Logic::createActor(std::string file) {
  Actor::Ptr actor = factory.createActor(file);
  ID::Type id = idGen.create();
  actors[id] = actor;
  
  auto event = std::make_shared<Events::ActorCreated>(id);
  eventManager->trigger(event);
  
  return id;
}

void Game::Logic::destroyActor(ID::Type id) {
  auto iter = actors.find(id);
  if (iter != actors.end()) {
    actors.erase(iter);
    
    auto event = std::make_shared<Events::ActorDestroyed>(id);
    eventManager->trigger(event);
  }
}

Game::Actor::Ptr Game::Logic::getActor(ID::Type id) {
  auto iter = actors.find(id);
  if (iter != actors.end()) {
    return iter->second;
  } else {
    return nullptr;
  }
}
