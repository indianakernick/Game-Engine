//
//  shader.hpp
//  Game Engine
//
//  Created by Indi Kernick on 6/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_platform_opengl_shader_hpp
#define engine_platform_opengl_shader_hpp

#ifdef USE_OPENGL

#include "../Interface/shader.hpp"
#include "opengl.hpp"
#include <cassert>

namespace Platform {
  class ShaderImpl final : public Shader {
  public:
    using Ptr = std::shared_ptr<ShaderImpl>;
  
    ShaderImpl(Type, GLuint);
    ~ShaderImpl();
  
    GLuint getID() const;
    
  private:
    GLuint id;
  };
}

#endif

#endif
