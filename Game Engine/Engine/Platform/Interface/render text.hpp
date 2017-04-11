//
//  render text.hpp
//  Game Engine
//
//  Created by Indi Kernick on 11/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_platform_interface_render_text_hpp
#define engine_platform_interface_render_text_hpp

#include "font.hpp"
#include "texture.hpp"
#include "shader program.hpp"
#include <glm/vec4.hpp>
#include <glm/vec2.hpp>
#include "window.hpp"

namespace Platform::RenderText {
  using Color = glm::vec4;

  struct AABB {
    glm::ivec2 tl;
    glm::ivec2 br;
  };

  class Context {
  public:
    using Ptr = std::shared_ptr<Context>;
    
    Context() = default;
    virtual ~Context() = default;
    
    virtual AABB bounds(glm::ivec2, Font::Ptr, const std::wstring &) = 0;
    virtual void render(glm::ivec2, Color, Font::Ptr, const std::wstring &) = 0;
  };
  
  Context::Ptr makeContext(Window::Ptr, ShaderProgram::Ptr);
}

#endif
