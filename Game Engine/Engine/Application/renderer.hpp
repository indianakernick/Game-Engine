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
#include <glm/vec4.hpp>

class Window;

class Renderer {
public:
  using Ptr = std::shared_ptr<Renderer>;
  
  struct Desc {
    int depthBits = 16;
    int stencilBits = 8;
    int colorBits = 32;
    glm::vec4 clearColor = {0.0f, 0.0f, 0.0f, 1.0f};
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
