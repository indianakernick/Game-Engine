//
//  actor.cpp
//  Game Engine
//
//  Created by Indi Kernick on 20/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "actor.hpp"

const Game::Actor::ID Game::Actor::NULL_ID = 0;
const Game::Component::ID Game::Actor::ALL_COMPONENTS = 255;

Game::Actor::Actor(ID id)
  : id(id) {}

Game::Actor::ID Game::Actor::getID() const {
  return id;
}

void Game::Actor::update(uint64_t delta) {
  flushMessages();
  for (auto i = components.begin(); i != components.end(); i++) {
    i->second->update(delta);
  }
}

void Game::Actor::addComponent(Component::Ptr comp) {
  if (comp->actor == this) {
    throw std::runtime_error("Tried to add component to same actor twice");
  } else if (comp->actor) {
    throw std::runtime_error("Tried to add component to more than one actor");
  }
  comp->actor = this;

  Component::ID id = comp->getID();
  bool inserted = components.insert({id, comp}).second;
  if (!inserted) {
    throw std::runtime_error("Duplicate component");
  }
}

Game::Actor::Message::Message(Component::ID from, Component::ID to,
                              int id, Any data)
  : from(from), to(to), id(id), data(data) {}

void Game::Actor::flushMessages() {
  while (!messageQueue.empty()) {
    const Message &message = messageQueue.front();
    if (message.to == ALL_COMPONENTS) {
      for (auto i = components.begin(); i != components.end(); i++) {
        i->second->onMessage(message.from, message.id, message.data);
      }
    } else {
      auto iter = components.find(message.to);
      if (iter != components.end()) {
        iter->second->onMessage(message.from, message.id, message.data);
      } else {
        throw std::runtime_error("Tried to send a message to a Component that doesn't exist");
      }
    }
    messageQueue.pop();
  }
}
