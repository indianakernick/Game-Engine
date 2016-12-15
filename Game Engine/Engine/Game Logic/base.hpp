//
//  base.hpp
//  Game Engine
//
//  Created by Indi Kernick on 15/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef base_hpp
#define base_hpp

#include "actor.hpp"
#include <map>
#include "../ID/rand.hpp"
#include "actor factory.hpp"
#include "../Event/manager.hpp"
#include "events.hpp"

namespace Game {
  class Logic {
  public:
    Logic(EventManager::Ptr eventManager);
    virtual ~Logic() = default;
    
    ID::Type createActor(std::string file);
    void destroyActor(ID::Type);
    Actor::Ptr getActor(ID::Type);
    
    ActorFactory &getFactory();
    
  private:
    std::map<ID::Type, Actor::Ptr> actors;
    ID::Rand idGen;
    ActorFactory factory;
    EventManager::Ptr eventManager;
  };
}

#endif
