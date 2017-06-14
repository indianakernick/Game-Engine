//
//  lamp component.hpp
//  Game Engine
//
//  Created by Indi Kernick on 11/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef game_logic_lamp_component_hpp
#define game_logic_lamp_component_hpp

#include "Events/lamp.hpp"
#include "tile component.hpp"

namespace Game {
  class Lamp final : public TileComponent {
  public:
    Lamp() = default;
    ~Lamp() = default;
    
    void init(const tinyxml2::XMLElement *) override {}
    void update(uint64_t) override;
    
  private:
    bool state = false;
    
    void setState(bool);
  };
}

#endif
