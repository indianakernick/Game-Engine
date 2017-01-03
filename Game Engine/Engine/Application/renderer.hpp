//
//  renderer.hpp
//  Game Engine
//
//  Created by Indi Kernick on 16/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_application_renderer_hpp
#define engine_application_renderer_hpp

#include <memory>
#include "../3D/color.hpp"

class Window;

class Renderer {
public:
  using Ptr = std::shared_ptr<Renderer>;
  
  struct Desc {
    int depthBits;
    int stencilBits;
    int colorBits;
    Color4F clearColor;
  };
  
  Renderer() = default;
  virtual ~Renderer() = default;
  
  virtual void init(Window *window, const Desc &) = 0;
  virtual void quit() = 0;
  
  //clear
  virtual void preRender() = 0;
  //present
  virtual void postRender() = 0;
};

#endif
