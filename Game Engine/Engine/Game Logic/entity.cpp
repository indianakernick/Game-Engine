//
//  newentity.cpp
//  game engine
//
//  Created by Indi Kernick on 10/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "entity.hpp"

Entity::Entity(ID id)
  : id(id) {}

void Entity::addComponent(std::shared_ptr<EntityComponent> comp) {
  if (components.find(comp->getID()) != components.end()) {
    throw std::runtime_error("Duplicate component");
  } else {
    components[comp->getID()] = comp;
  }
}
