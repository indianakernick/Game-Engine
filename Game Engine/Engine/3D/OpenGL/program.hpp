//
//  program.hpp
//  opengl
//
//  Created by Indi Kernick on 22/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_opengl_program_hpp
#define engine_3d_opengl_program_hpp

//#include "../../Application/opengl.hpp"

#ifdef __gl_h_

#include "shader.hpp"

namespace Graphics3D {
  class ProgramOpenGL {
  public:
    ProgramOpenGL();
    ProgramOpenGL(const ProgramOpenGL &) = delete;
    virtual ~ProgramOpenGL();
    
    ProgramOpenGL &operator=(const ProgramOpenGL &) = delete;
    
    virtual void load() = 0;
    virtual void enableVertexArray() = 0;
    virtual void disableVertexArray() = 0;
    
    void link();
    void bind() const;
    void unbind() const;
    
    GLuint getID() const;
  protected:
    void attach(const ShaderOpenGL &);
    void setupShaders(const std::string &vert, const std::string &frag);
    
    GLint getAttr(const char *);
    GLint getUniform(const char *);
    
    void printInfoLog();
  private:
    GLuint id;
  };
}

#endif

#endif
