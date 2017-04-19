//
//  input manager.hpp
//  Game Engine
//
//  Created by Indi Kernick on 2/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_platform_interface_input_manager_hpp
#define engine_platform_interface_input_manager_hpp

#include "window manager.hpp"
#include "../../Input/event.hpp"
#include "../../Event/manager.hpp"
#include "../../Utils/profiler.hpp"
#include "../../Utils/instance limiter.hpp"

namespace Platform {
  class InputManager : private ForceSingleton<InputManager> {
  public:
    using Ptr = std::shared_ptr<InputManager>;
    
    InputManager(std::weak_ptr<WindowManager>);
    virtual ~InputManager() = default;
    
    void update();
    
  protected:
    std::weak_ptr<WindowManager> weakWindowManager;
  
    void sendEvent(Game::Event::Ptr);
    
    virtual void sendEvents() = 0;
  };
}

#endif
