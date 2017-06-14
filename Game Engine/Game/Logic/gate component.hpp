//
//  gate component.hpp
//  Game Engine
//
//  Created by Indi Kernick on 11/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef game_logic_gate_component_hpp
#define game_logic_gate_component_hpp

#include "Events/gate.hpp"
#include "tile component.hpp"

namespace Game {
  class Gate final : public TileComponent {
  public:
    Gate();
    ~Gate();
    
    void init(const tinyxml2::XMLElement *) override {}
    void update(uint64_t) override;
    
  private:
    const EventManager::ListenerID tableChangeID;
    GateTable table;
    
    void onTableChange(Events::GateTableChange::Ptr);
  };
}

#endif
