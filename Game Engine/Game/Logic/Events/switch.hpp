//
//  switch.hpp
//  Game Engine
//
//  Created by Indi Kernick on 14/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef game_logic_events_switch_hpp
#define game_logic_events_switch_hpp

#include "../tile.hpp"
#include "../../../Engine/Event/event.hpp"

namespace Game {
  namespace Events {
    constexpr char SWITCH_ON_NAME[] = "Switch On";
    
    class SwitchOn final : public StaticEvent<SwitchOn, SWITCH_ON_NAME> {
    public:
      explicit SwitchOn(TilePos);
      ~SwitchOn() = default;
      
      const TilePos pos;
    };
    
    constexpr char SWITCH_OFF_NAME[] = "Switch Off";
    
    class SwitchOff final : public StaticEvent<SwitchOff, SWITCH_OFF_NAME> {
    public:
      explicit SwitchOff(TilePos);
      ~SwitchOff() = default;
      
      const TilePos pos;
    };
  }
}

#endif
