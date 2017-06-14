//
//  lamp.hpp
//  Game Engine
//
//  Created by Indi Kernick on 14/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef game_logic_events_lamp_hpp
#define game_logic_events_lamp_hpp

#include "../tile.hpp"
#include "../../../Engine/Event/event.hpp"

namespace Game {
  namespace Events {
    constexpr char LAMP_ON_NAME[] = "Lamp On";
  
    class LampOn final : public StaticEvent<LampOn, LAMP_ON_NAME> {
    public:
      explicit LampOn(TilePos);
      ~LampOn() = default;
      
      const TilePos pos;
    };
    
    constexpr char LAMP_OFF_NAME[] = "Lamp Off";
    
    class LampOff final : public StaticEvent<LampOff, LAMP_OFF_NAME> {
    public:
      explicit LampOff(TilePos);
      ~LampOff() = default;
      
      const TilePos pos;
    };
  }
}

#endif
