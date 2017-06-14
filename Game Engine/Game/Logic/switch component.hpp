//
//  switch component.hpp
//  Game Engine
//
//  Created by Indi Kernick on 11/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef game_logic_switch_component_hpp
#define game_logic_switch_component_hpp

#include "Events/switch.hpp"
#include "tile component.hpp"

namespace Game {
  class Switch final : public TileComponent {
  public:
    Switch();
    ~Switch();
    
    void init(const tinyxml2::XMLElement *) override {}
    void update(uint64_t) override;
    
  private:
    EventManager::ListenerID onID, offID;
    bool state = false;
    
    void onSwitchOn(Events::SwitchOn::Ptr);
    void onSwitchOff(Events::SwitchOff::Ptr);
  };
}

#endif
