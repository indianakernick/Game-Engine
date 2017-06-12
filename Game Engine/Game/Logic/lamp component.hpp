//
//  lamp component.hpp
//  Game Engine
//
//  Created by Indi Kernick on 11/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef game_logic_lamp_component_hpp
#define game_logic_lamp_component_hpp

#include "tile component.hpp"

namespace Game {
  namespace Events {
    constexpr char LAMP_ON_NAME[] = "Lamp On";
  
    class LampOn final : public StaticEvent<LampOn, LAMP_ON_NAME> {
    public:
      explicit LampOn(Actor::ID);
      ~LampOn() = default;
      
      const Actor::ID lampID;
    };
    
    constexpr char LAMP_OFF_NAME[] = "Lamp Off";
    
    class LampOff final : public StaticEvent<LampOff, LAMP_OFF_NAME> {
    public:
      explicit LampOff(Actor::ID);
      ~LampOff() = default;
      
      const Actor::ID lampID;
    };
  }

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
