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

#include "../../Resource/Handles/opengl shader.hpp"
#include "../../Utils/logger.hpp"
#include "../../Application/global resource cache.hpp"
#include "attrib pointer.hpp"
#include "set uniform.hpp"
#include "constants.hpp"

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
    
    void bind() const;
    void unbind() const;
    bool isBound() const;
    
    GLuint getID() const;
  protected:
    void attach(const std::string &path);
    void setupShaders(const std::string &vert, const std::string &frag);
    
    GLint getUniform(const char *);
    
    template <GLint ATTR>
    void enable() {
      glEnableVertexAttribArray(ATTR);
    }
    template <GLint ATTR>
    void disable() {
      glDisableVertexAttribArray(ATTR);
    }
    template <GLint ATTR, GLsizei SIZE>
    void enableArray() {
      static_assert(SIZE > 0, "Cannot have array of zero size");
      for (GLint a = ATTR; a < ATTR + SIZE; a++) {
        glEnableVertexAttribArray(a);
      }
    }
    template <GLint ATTR, GLsizei SIZE>
    void disableArray() {
      static_assert(SIZE > 0, "Cannot have array of zero size");
      for (GLint a = ATTR; a < ATTR + SIZE; a++) {
        glDisableVertexAttribArray(a);
      }
    }
    
    void printInfoLog();
  private:
    GLuint id;
    const char *name;
    bool linkStatus = false;
    
    static GLuint bound;
  };
}

#endif

#endif
