//
//  shader.hpp
//  opengl
//
//  Created by Indi Kernick on 21/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_opengl_shader_hpp
#define engine_3d_opengl_shader_hpp

//#include "../../Application/opengl.hpp"

#ifdef __gl_h_

#include <iostream>
#include <fstream>

namespace Graphics3D {
  class ShaderOpenGL {
  public:
    ShaderOpenGL(GLenum type);
    ShaderOpenGL(const ShaderOpenGL &) = delete;
    ~ShaderOpenGL();
    
    ShaderOpenGL &operator=(const ShaderOpenGL &) = delete;
    
    void load(const std::string &);
    void printInfoLog();
    
    GLuint getID() const;
  private:
    GLuint id;
    //for logging
    std::string name;
  };
}

#endif

#endif
