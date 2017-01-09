//
//  program.hpp
//  opengl
//
//  Created by Indi Kernick on 22/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_opengl_program_hpp
#define engine_3d_opengl_program_hpp

#ifdef USE_OPENGL

#include "../../Resource/Descriptions/opengl shader.hpp"
#include "../../Utils/logger.hpp"
#include "../../Application/global resource cache.hpp"

namespace Graphics3D {
  class ProgramOpenGL {
  public:
    ProgramOpenGL(const char *);
    ProgramOpenGL(const ProgramOpenGL &) = delete;
    virtual ~ProgramOpenGL();
    
    ProgramOpenGL &operator=(const ProgramOpenGL &) = delete;
    
    virtual void load() = 0;
    virtual void enableAll() = 0;
    virtual void disableAll() = 0;
    
    void link();
    void validate();
    
    void bind() const;
    void unbind() const;
    
    GLuint getID() const;
  protected:
    void attach(const std::string &path);
    void setupShaders(const std::string &vert, const std::string &frag);
    
    GLint getAttr(const char *);
    GLint getUniform(const char *);
    
    void printInfoLog();
  private:
    GLuint id;
    const char *name;
    bool linkStatus = false;
  };
}

#endif

#endif
