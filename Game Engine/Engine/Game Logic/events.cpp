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

const Event::Type ActorCreated::TYPE = EvtTypeGen::make();
const Event::Type ActorDestroyed::TYPE = EvtTypeGen::make();

ActorCreated::ActorCreated(Actor::ID actor)
  : actor(actor) {}

Event::Type ActorCreated::getType() const {
  return TYPE;
}

const char *ActorCreated::getName() const {
  return "Actor Created";
}

ActorDestroyed::ActorDestroyed(Actor::ID actor)
  : actor(actor) {}

Event::Type ActorDestroyed::getType() const {
  return TYPE;
}

const char *ActorDestroyed::getName() const {
  return "Actor Destroyed";
}
