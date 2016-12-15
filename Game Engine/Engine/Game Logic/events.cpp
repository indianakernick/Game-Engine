//
//  events.cpp
//  Game Engine
//
//  Created by Indi Kernick on 15/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "events.hpp"

const Game::Event::Type Game::Events::ActorCreated::TYPE = ID::GUID<Event::Type>::get();
const Game::Event::Type Game::Events::ActorDestroyed::TYPE = ID::GUID<Event::Type>::get();

Game::Events::ActorCreated::ActorCreated(Actor::ID actor)
  : actor(actor) {}

Game::Event::Type Game::Events::ActorCreated::getType() const {
  return TYPE;
}

std::string Game::Events::ActorCreated::getName() const {
  return "Actor Created";
}

Game::Events::ActorDestroyed::ActorDestroyed(Actor::ID actor)
  : actor(actor) {}

Game::Event::Type Game::Events::ActorDestroyed::getType() const {
  return TYPE;
}

std::string Game::Events::ActorDestroyed::getName() const {
  return "Actor Destroyed";
}
