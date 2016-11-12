//
//  entitycomponent.hpp
//  game engine
//
//  Created by Indi Kernick on 10/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef entitycomponent_hpp
#define entitycomponent_hpp

#include <memory>

class Entity;

class EntityComponent {
public:
  using ID = char;

  EntityComponent() = default;
  virtual ~EntityComponent() = default;
  
  virtual ID getID() const = 0;
  
protected:
  std::weak_ptr<Entity> entity;
private:
  
};

#endif