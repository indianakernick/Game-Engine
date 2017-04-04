//
//  window.hpp
//  Game Engine
//
//  Created by Indi Kernick on 2/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_platform_interface_window_hpp
#define engine_platform_interface_window_hpp

#include "../../Geometry/size.hpp"
#include <string>
#include <memory>

namespace Platform {
  class Window {
  public:
    using Ptr = std::shared_ptr<Window>;
    
    struct Desc {
      std::string title;
      Geometry::Size size = {1280, 720};
      bool resizable = false;
      bool fullscreen = false;
    };
    
    Window() = default;
    Window(const Window &) = delete;
    Window(Window &&) = default;
    virtual ~Window() = default;
    
    Window &operator=(const Window &) = delete;
    Window &operator=(Window &&) = default;
    
    virtual void title(const std::string &) = 0;
    virtual std::string title() const = 0;
    
    virtual void size(Geometry::Size) = 0;
    virtual Geometry::Size size() const = 0;
    
    virtual void relMouse(bool) = 0;
    virtual bool relMouse() const = 0;
    
    virtual void captureMouse(bool) = 0;
    virtual bool captureMouse() const = 0;
    
    virtual void fullscreen(bool) = 0;
    virtual bool fullscreen() const = 0;
    
    virtual void raise() = 0;
  };
}

#endif
