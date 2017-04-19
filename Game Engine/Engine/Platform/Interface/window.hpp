//
//  window.hpp
//  Game Engine
//
//  Created by Indi Kernick on 2/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_platform_interface_window_hpp
#define engine_platform_interface_window_hpp

#include <string>
#include <memory>
#include <glm/vec2.hpp>

namespace Platform {
  class Window {
  public:
    struct Desc {
      std::string title;
      glm::ivec2 size = {1280, 720};
      bool resizable = false;
    };
    
    Window() = default;
    Window(const Window &) = delete;
    Window(Window &&) = default;
    virtual ~Window() = default;
    
    Window &operator=(const Window &) = delete;
    Window &operator=(Window &&) = default;
    
    virtual void title(const std::string &) = 0;
    virtual std::string title() const = 0;
    
    virtual void pos(glm::ivec2) = 0;
    virtual glm::ivec2 pos() const = 0;
    
    virtual void center() = 0;
    virtual void center(bool, bool) = 0;
    
    virtual void size(glm::ivec2) = 0;
    virtual glm::ivec2 size() const = 0;
    
    virtual void opacity(float) = 0;
    virtual float opacity() const = 0;
    
    virtual void relMouse(bool) = 0;
    virtual bool relMouse() const = 0;
    
    virtual void captureMouse(bool) = 0;
    virtual bool captureMouse() const = 0;
    
    virtual void raise() = 0;
  };
}

#endif
