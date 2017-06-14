//
//  timer component.hpp
//  Game Engine
//
//  Created by Indi Kernick on 11/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef game_logic_timer_component_hpp
#define game_logic_timer_component_hpp

#include <queue>
#include "Events/timer.hpp"
#include "tile component.hpp"

namespace Game {
  class Timer final : public TileComponent {
  public:
    Timer();
    ~Timer();
    
    void init(const tinyxml2::XMLElement *) override {}
    void update(uint64_t) override;
    
  private:
    std::queue<bool> flow;
    EventManager::ListenerID durChangeID;
    TimerDur duration = 0;
  
    void onDurChange(Events::TimerDurChange::Ptr);
  };
}

#endif
