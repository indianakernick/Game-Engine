//
//  pulse component.hpp
//  Game Engine
//
//  Created by Indi Kernick on 11/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef game_logic_pulse_component_hpp
#define game_logic_pulse_component_hpp

#include "Events/pulse.hpp"
#include "tile component.hpp"

namespace Game {
  class Pulse final : public TileComponent {
  public:
    Pulse();
    ~Pulse();
    
    void init(const tinyxml2::XMLElement *) override {}
    void update(uint64_t) override;
  
  private:
    const EventManager::ListenerID durChangeID;
    PulseDur offDuration = 1;
    PulseDur onDuration = 1;
    PulseDur elapsed = 0;
    bool state = false;
    
    void onDurChange(Events::PulseDurChange::Ptr);
  };
}

#endif
