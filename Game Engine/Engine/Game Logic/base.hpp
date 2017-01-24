//
//  base.hpp
//  Game Engine
//
//  Created by Indi Kernick on 15/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_game_logic_base_hpp
#define engine_game_logic_base_hpp

#include "actor.hpp"
#include <map>
#include "../ID/generator.hpp"
#include "actor factory.hpp"
#include "../Event/manager.hpp"
#include "events.hpp"
#include "../Game View/base.hpp"
#include "../Resource/id.hpp"
#include "../Anim/process manager.hpp"

namespace Game {
  class Logic {
  private:
    template <typename T>
    using IDMap = std::map<typename T::ID, typename T::Ptr>;
  public:
    using Ptr = std::shared_ptr<Logic>;
    using Actors = IDMap<Actor>;
    using Views = IDMap<View>;
  
    Logic() = default;
    virtual ~Logic() = default;
    
    virtual void init() {};
    virtual void update(uint64_t);
    virtual void quit();
    
    void attachView(Game::View::Ptr view, Actor::ID actor);
    void detachView(Game::View::Ptr view);
    
    Actor::ID createActor(const Resource::ID &file);
    void destroyActor(Actor::ID);
    Actor::Ptr getActor(Actor::ID);
    
    ActorFactory &getFactory();
    Views &getViews();
  protected:
    void updateActors(uint64_t);
  private:
    Actors actors;
    Views views;
    
    ID::Generator<View::ID> idGen;
    ActorFactory factory;
    ProcessManager processManager;
  };
}

#endif
