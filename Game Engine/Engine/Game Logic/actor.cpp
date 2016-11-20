//
//  actor.cpp
//  Game Engine
//
//  Created by Indi Kernick on 20/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "actor.hpp"

Actor::Actor(ID id)
  : id(id) {}

void Actor::destroy() {
  components.clear();
}

Actor::ID Actor::getID() const {
  return id;
}

void Actor::update(double delta) {
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
