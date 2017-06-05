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

ActorCreated::ActorCreated(Actor::ID actor)
  : actor(actor) {}

Event::Type ActorCreated::getType() const {
  return GetEventType<ActorCreated>::get();
}

const char *ActorCreated::getName() const {
  return "Actor Created";
}

ActorDestroyed::ActorDestroyed(Actor::ID actor)
  : actor(actor) {}

Event::Type ActorDestroyed::getType() const {
  return GetEventType<ActorDestroyed>::get();
}

const char *ActorDestroyed::getName() const {
  return "Actor Destroyed";
}
