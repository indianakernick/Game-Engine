//
//  events.cpp
//  Game Engine
//
//  Created by Indi Kernick on 15/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "events.hpp"

using namespace Game;
using namespace Game::Events;

ActorCreated::ActorCreated(const Actor::ID actor)
  : actor(actor) {}

ActorDestroyed::ActorDestroyed(const Actor::ID actor)
  : actor(actor) {}
