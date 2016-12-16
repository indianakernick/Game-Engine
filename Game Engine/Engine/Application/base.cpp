//
//  base.cpp
//  Game Engine
//
//  Created by Indi Kernick on 14/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "base.hpp"

void Game::App::init() {
  eventManager = std::make_shared<EventManager>();
  gameLogic = std::make_shared<Logic>(eventManager);
  cache = std::make_shared<Resource::Cache>(Math::Byte::MEGA * 512);
}

void Game::App::quit() {
  cache.reset();
  gameLogic.reset();
  eventManager.reset();
}
