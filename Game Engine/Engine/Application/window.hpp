//
//  window.hpp
//  Game Engine
//
//  Created by Indi Kernick on 16/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_application_window_hpp
#define engine_application_window_hpp

#include "../Geometry/size.hpp"
#include <string>
#include "renderer.hpp"
#include "../Input/manager.hpp"

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
  virtual ~Window() = default;
  
  virtual void open(const Desc &) = 0;
  virtual Renderer::Ptr createRenderer(const Renderer::Desc &) = 0;
  virtual Input::Manager::Ptr createInputManager() = 0;
  virtual void close() = 0;
  
  virtual void changeTitle(std::string) = 0;
  virtual void resize(Geometry::Size) = 0;
  
  virtual void relMouse(bool) = 0;
  virtual bool relMouse() = 0;
  
  virtual void captureMouse(bool) = 0;
  virtual bool captureMouse() = 0;
  
  virtual void fullscreen(bool) = 0;
  virtual bool fullscreen() = 0;
  
  const std::string &getTitle() const;
  Geometry::Size getSize() const;
  
protected:
  std::string title;
  Geometry::Size size;
};

#endif
