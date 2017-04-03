//
//  window library.hpp
//  Game Engine
//
//  Created by Indi Kernick on 2/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_platform_interface_window_library_hpp
#define engine_platform_interface_window_library_hpp

#include <string>
#include <glm/vec2.hpp>
#include "window.hpp"
#include "rendering context.hpp"
#include "input manager.hpp"

namespace Platform {
  void initLib();
  void quitLib();
  Window::Ptr openWindow(const Window::Desc &);
  RenderingContext::Ptr createRenderingContext(Window::Ptr, const RenderingContext::Desc &);
  InputManager::Ptr createInputManager(Window::Ptr);
  std::string getSaveDir(std::string, std::string);
  uint64_t getSystemRAM();
  glm::vec2 getDisplayDPI();
}

#endif
