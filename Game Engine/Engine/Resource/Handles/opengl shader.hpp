//
//  opengl shader.hpp
//  Game Engine
//
//  Created by Indi Kernick on 8/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_descriptions_opengl_shader_hpp
#define engine_resource_descriptions_opengl_shader_hpp

#ifdef USE_OPENGL

#include "../../Application/opengl.hpp"
#include "../handle.hpp"

namespace Res {
  class ShaderOpenGL : public Handle {
  public:
    using Ptr = std::shared_ptr<ShaderOpenGL>;
    
    ShaderOpenGL(GLuint id, GLenum type);
    ~ShaderOpenGL();
    
    GLuint getID() const;
    GLenum getType() const;
  private:
    GLuint id;
    GLenum type;
  };
}

#endif

#endif
