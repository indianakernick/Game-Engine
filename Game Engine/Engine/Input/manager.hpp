//
//  manager.hpp
//  Game Engine
//
//  Created by Indi Kernick on 4/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_input_manager_hpp
#define engine_input_manager_hpp

#include "event.hpp"
#include "../Event/manager.hpp"
#include "../Utils/profiler.hpp"

namespace Input {
  class Manager {
  public:
    using Ptr = std::shared_ptr<Manager>;
  
    Manager(Geometry::Size);
    virtual ~Manager() = default;
    
    void update();
  protected:
    bool keyState[Key::NUM_OF_KEYS] = {0};
    bool mouseState[MButton::NUM_OF_BUTTONS] = {0};
    Geometry::Point mousePos;
    Geometry::Size windowSize;
    
    void sendEvent(Game::Event::Ptr);
  
    virtual void sendEvents() = 0;
  };
};

#endif
