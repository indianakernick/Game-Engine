//
//  newentity.hpp
//  game engine
//
//  Created by Indi Kernick on 10/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef newentity_hpp
#define newentity_hpp

#include <map>
#include <memory>
#include "entitycomponent.hpp"
#include <ID/interface.hpp>

class Entity {
public:
  using ID = ID::Type;
  
  Entity(ID);
  ~Entity() = default;
  
  template<typename T>
  std::weak_ptr<T> getComponent(EntityComponent::ID id) {
    auto iter = components.find(id);
    if (iter != components.end()) {
      std::shared_ptr<EntityComponent> compPtr(iter->second);
      std::shared_ptr<T> outPtr(std::dynamic_pointer_cast<T>(compPtr));
      return std::weak_ptr<T>(outPtr);
    } else {
      throw std::runtime_error("No component with that ID was found");
    }
  }
private:
  std::map<EntityComponent::ID, std::shared_ptr<EntityComponent>> components;
  ID id;
  
  void addComponent(std::shared_ptr<EntityComponent>);
};

#endif