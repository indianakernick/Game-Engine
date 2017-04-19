//
//  window manager.hpp
//  Game Engine
//
//  Created by Indi Kernick on 18/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_platform_sdl_window_manager_hpp
#define engine_platform_sdl_window_manager_hpp

#ifdef USE_SDL

#include "../Interface/window manager.hpp"
#include "window.hpp"
#include <unordered_map>
#include "../../Utils/logger.hpp"
#include "../../Utils/bool enable.hpp"

namespace Platform {
  class WindowManagerImpl final : public WindowManager {
  public:
    using Ptr = std::shared_ptr<WindowManagerImpl>;
    using WindowID = Uint32;
    
    WindowManagerImpl() = default;
    ~WindowManagerImpl() = default;
    
    std::weak_ptr<Window> openWindow(const Window::Desc &) override;
    void closeWindow(std::weak_ptr<Window>) override;
    void closeAllWindows() override;
    std::weak_ptr<Window> getWindow(WindowID);
    void closeWindow(WindowID);
  
  private:
    std::unordered_map<WindowID, std::shared_ptr<Window>> windows;
  };
}

#endif

#endif
