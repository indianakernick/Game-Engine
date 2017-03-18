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
#include "../Event/type gen.hpp"
#include "actor.hpp"

namespace Game {
  namespace Events {
    class ActorCreated : public Event {
    public:
      static const Event::Type TYPE;
      
      ActorCreated(Actor::ID);
      
      Type getType() const override;
      const char *getName() const override;
      
      const Actor::ID actor;
    };
    
    class ActorDestroyed : public Event {
    public:
      static const Event::Type TYPE;
      
      ActorDestroyed(Actor::ID);
      
      Type getType() const override;
      const char *getName() const override;
      
      const Actor::ID actor;
    };
  };
};

#endif
