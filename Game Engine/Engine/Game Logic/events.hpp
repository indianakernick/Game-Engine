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
    class ActorCreated final : public Event {
    public:
      explicit ActorCreated(Actor::ID);
      
      Type getType() const override;
      const char *getName() const override;
      
      const Actor::ID actor;
    };
    
    class ActorDestroyed final : public Event {
    public:
      explicit ActorDestroyed(Actor::ID);
      
      Type getType() const override;
      const char *getName() const override;
      
      const Actor::ID actor;
    };
  };
};

#endif
