//
//  base.hpp
//  Game Engine
//
//  Created by Indi Kernick on 15/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_game_logic_base_hpp
#define engine_game_logic_base_hpp

#include <map>
#include "actor.hpp"
#include "events.hpp"
#include "../ID/local.hpp"
#include "actor factory.hpp"
#include "../Event/manager.hpp"
#include "../Game View/base.hpp"
#include "../Utils/profiler.hpp"

namespace Game {
  class Logic {
  public:
    using Ptr = std::shared_ptr<Logic>;
    using Views = std::map<View::ID, View::Ptr>;
  
    Logic() = default;
    virtual ~Logic() = default;
    
    virtual void init();
    virtual void update(uint64_t);
    virtual void quit();
    
    void attachView(Game::View::Ptr, Actor::ID);
    void detachView(Game::View::Ptr);
    
    Actor::ID createActor(const std::string &);
    void destroyActor(Actor::ID);
    
    ActorFactory &getFactory();
    Views &getViews();
    
  private:
    Views views;
    
    ID::Local<View::ID> idGen;
    ActorFactory factory;
    
    virtual void createActorImpl(Actor::ID, Actor::Ptr) = 0;
    virtual bool destroyActorImpl(Actor::ID) = 0;
  };
}

#endif
