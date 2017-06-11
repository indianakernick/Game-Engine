//
//  pulse component.hpp
//  Game Engine
//
//  Created by Indi Kernick on 11/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef game_logic_pulse_component_hpp
#define game_logic_pulse_component_hpp

#include "tile component.hpp"
#include "../../Engine/Event/manager.hpp"
#include "../../Engine/Game Logic/actor.hpp"
#include "../../Engine/Utils/member function.hpp"

namespace Game {
  namespace Events {
    constexpr char PULSE_DUR_CHANGE_NAME[] = "Pulse Duration Change";
    
    class PulseDurChange final : public StaticEvent<PulseDurChange, PULSE_DUR_CHANGE_NAME> {
    public:
      PulseDurChange(Actor::ID, uint32_t, uint32_t);
      
      const Actor::ID pulseID;
      const uint32_t onDuration;
      const uint32_t offDuration;
    };
  }
  
  class Pulse final : public TileComponent {
  public:
    Pulse();
    ~Pulse();
    
    void init(const tinyxml2::XMLElement *) override {}
    void update(uint64_t) override;
  
  private:
    EventManager::ListenerID durChangeID;
    uint32_t offDuration = 1;
    uint32_t onDuration = 1;
    uint32_t elapsed = 0;
    bool state = false;
    
    void onDurChange(Events::PulseDurChange::Ptr);
  };
}

#endif
