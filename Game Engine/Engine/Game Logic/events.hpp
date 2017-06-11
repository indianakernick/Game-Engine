//
//  events.hpp
//  Game Engine
//
//  Created by Indi Kernick on 15/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_game_logic_events_hpp
#define engine_game_logic_events_hpp

#include "../Event/event.hpp"
#include "actor.hpp"

namespace Game {
  namespace Events {
    constexpr char ACTOR_CREATED_NAME[] = "Actor Created";
  
    class ActorCreated final : public StaticEvent<ActorCreated, ACTOR_CREATED_NAME> {
    public:
      explicit ActorCreated(Actor::ID);
      
      const Actor::ID actor;
    };
    
    constexpr char ACTOR_DESTROYED_NAME[] = "Actor Destroyed";
    
    class ActorDestroyed final : public StaticEvent<ActorDestroyed, ACTOR_DESTROYED_NAME> {
    public:
      explicit ActorDestroyed(Actor::ID);
      
      const Actor::ID actor;
    };
  };
};

#endif
