//
//  shader program.hpp
//  Game Engine
//
//  Created by Indi Kernick on 8/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_platform_opengl_shader_program_hpp
#define engine_platform_opengl_shader_program_hpp

#ifdef USE_OPENGL

#include "../Interface/shader program.hpp"
#include "opengl.hpp"

namespace Platform {
  class ShaderProgramImpl final : public ShaderProgram {
  public:
    using Ptr = std::shared_ptr<ShaderProgramImpl>;
  
    ShaderProgramImpl(const std::string &, GLuint);
    ~ShaderProgramImpl();
    
    GLuint getID() const;
  
  private:
    GLuint id;
  };
}

#endif

#endif
