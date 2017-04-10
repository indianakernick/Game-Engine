//
//  render 2d.hpp
//  Game Engine
//
//  Created by Indi Kernick on 8/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_platform_interface_render_2d_hpp
#define engine_platform_interface_render_2d_hpp

#include "texture.hpp"
#include <glm/vec2.hpp>
#include <glm/vec4.hpp>
#include "shader program.hpp"
#include <array>

namespace Platform::Render2D {
  using Color = glm::vec4;
  using Height = int;
  using Bounds = std::array<glm::vec2, 4>;
  enum Corner : size_t {
    TL,
    TR,
    BR,
    BL
  };

  ///A list of objects to be rendered
  class List {
  public:
    using Ptr = std::shared_ptr<List>;
  
    List() = default;
    virtual ~List() = default;
    
    virtual void push(Texture::Ptr, Color, Height, Bounds) = 0;
    virtual void zsort() = 0;
    virtual void clear() = 0;
  };
  
  class Context {
  public:
    using Ptr = std::shared_ptr<Context>;
  
    Context() = default;
    virtual ~Context() = default;
    
    virtual void render(const List::Ptr) = 0;
  };
  
  List::Ptr makeList();
  Context::Ptr makeContext(ShaderProgram::Ptr);
}

#endif
