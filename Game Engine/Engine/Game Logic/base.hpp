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

namespace Game {
  class Logic {
  public:
    using Ptr = std::shared_ptr<Logic>;
  
    Logic(EventManager::Ptr eventManager);
    virtual ~Logic() = default;
    
    virtual void update(uint64_t);
    
    void attachView(Game::View::Ptr view, Actor::ID actor);
    void detachView(Game::View::Ptr view);
    
    Actor::ID createActor(std::string file);
    void destroyActor(Actor::ID);
    Actor::Ptr getActor(Actor::ID);
    
    ActorFactory &getFactory();
  protected:
    void updateActors(uint64_t);
  private:
    template <typename T>
    using IDMap = std::map<typename T::ID, typename T::Ptr>;
    IDMap<Actor> actors;
    IDMap<View> views;
    
    ID::Generator<View::ID> idGen;
    ActorFactory factory;
    EventManager::Ptr eventManager;
  };
}

#endif
