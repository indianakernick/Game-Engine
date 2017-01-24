//
//  component.cpp
//  Game Engine
//
//  Created by Indi Kernick on 10/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "component.hpp"

void Game::Component::broadcastMessage(int id, Any data) {
  assert(actor);
  actor->messageQueue.emplace(getID(), Actor::ALL_COMPONENTS, id, data);
}

void Game::Component::sendMessage(Component::ID to, int id, Any data) {
  assert(actor);
  actor->messageQueue.emplace(getID(), to, id, data);
}
