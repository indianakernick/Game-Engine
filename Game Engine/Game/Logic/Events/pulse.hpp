//
//  pulse.hpp
//  Game Engine
//
//  Created by Indi Kernick on 14/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef game_logic_events_pulse_hpp
#define game_logic_events_pulse_hpp

#include "../tile.hpp"
#include "../../../Engine/Event/event.hpp"

namespace Game {
  using PulseDur = uint32_t;

  namespace Events {
    constexpr char PULSE_DUR_CHANGE_NAME[] = "Pulse Duration Change";
    
    class PulseDurChange final : public StaticEvent<PulseDurChange, PULSE_DUR_CHANGE_NAME> {
    public:
      PulseDurChange(TilePos, PulseDur, PulseDur);
      ~PulseDurChange() = default;
      
      const TilePos pos;
      const PulseDur onDuration;
      const PulseDur offDuration;
    };
  }
}

#endif
