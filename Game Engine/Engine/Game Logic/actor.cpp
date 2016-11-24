//
//  actor.cpp
//  Game Engine
//
//  Created by Indi Kernick on 20/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "actor.hpp"

const Component::ID Actor::ALL_COMPONENTS = 255;

Actor::Actor(ID id)
  : id(id) {}

void Actor::destroy() {
  components.clear();
}

Actor::ID Actor::getID() const {
  return id;
}

void Actor::update(double delta) {
  flushMessages();
  for (auto i = components.begin(); i != components.end(); i++) {
    i->second->update(delta);
  }
}

void Actor::addComponent(ComponentPtr comp) {
  Component::ID id = comp->getID();
  bool inserted = components.insert({id, comp}).second;
  if (!inserted) {
    throw std::runtime_error("Duplicate component");
  }
}

Actor::Message::Message(Component::ID from, Component::ID to, int id, void *data)
  : from(from), to(to), id(id), data(data) {}

void Actor::flushMessages() {
  while (!messageQueue.empty()) {
    Message &message = messageQueue.front();
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
  }
}
