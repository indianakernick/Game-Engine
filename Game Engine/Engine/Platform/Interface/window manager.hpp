//
//  window manager.hpp
//  Game Engine
//
//  Created by Indi Kernick on 18/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_platform_interface_window_manager_hpp
#define engine_platform_interface_window_manager_hpp

#include "../../Utils/instance limiter.hpp"
#include "window.hpp"

namespace Platform {
  class WindowManager : private ForceSingleton<WindowManager> {
  public:
    using Ptr = std::shared_ptr<WindowManager>;
    
    WindowManager() = default;
    virtual ~WindowManager() = default;
    
    virtual std::weak_ptr<Window> openWindow(const Window::Desc &) = 0;
    virtual void closeWindow(std::weak_ptr<Window>) = 0;
    virtual void closeAllWindows() = 0;
  };
}

#endif
