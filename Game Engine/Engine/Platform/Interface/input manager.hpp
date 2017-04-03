//
//  input manager.hpp
//  Game Engine
//
//  Created by Indi Kernick on 2/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_platform_interface_input_manager_hpp
#define engine_platform_interface_input_manager_hpp

#include "../../Input/event.hpp"
#include "../../Event/manager.hpp"
#include "../../Utils/profiler.hpp"

namespace Platform {
  class InputManager {
  public:
    using Ptr = std::shared_ptr<InputManager>;
    
    InputManager(Geometry::Size);
    virtual ~InputManager() = default;
    
    void update();
    
  protected:
    bool keyState[Input::Key::NUM_OF_KEYS] = {0};
    bool mouseState[Input::MButton::NUM_OF_BUTTONS] = {0};
    Geometry::Point mousePos;
    Geometry::Size windowSize;
    
    void sendEvent(Game::Event::Ptr);
    
    virtual void sendEvents() = 0;
  };
}

#endif