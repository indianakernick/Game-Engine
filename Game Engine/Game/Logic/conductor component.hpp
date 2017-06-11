//
//  conductor component.hpp
//  Game Engine
//
//  Created by Indi Kernick on 11/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef game_logic_conductor_component_hpp
#define game_logic_conductor_component_hpp

#include "tile component.hpp"

namespace Game {
  class Conductor final : public TileComponent {
  public:
    Conductor() = default;
    ~Conductor() = default;
    
    void init(const tinyxml2::XMLElement *) override {}
    void update(uint64_t) override;
  };
}

#endif
