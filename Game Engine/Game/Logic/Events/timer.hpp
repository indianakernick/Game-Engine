//
//  timer.hpp
//  Game Engine
//
//  Created by Indi Kernick on 14/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef game_logic_events_timer_hpp
#define game_logic_events_timer_hpp

#include "../tile.hpp"
#include "../../../Engine/Event/event.hpp"

namespace Game {
  namespace Events {
    constexpr char TIMER_DUR_CHANGE_NAME[] = "Timer Duration Change";
    
    class TimerDurChange final : public StaticEvent<TimerDurChange, TIMER_DUR_CHANGE_NAME> {
    public:
      TimerDurChange(TilePos, uint32_t);
      ~TimerDurChange() = default;
      
      const TilePos pos;
      const uint32_t duration;
    };
  }
}

#endif
