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
#include "shader path.hpp"
#include "../program type.hpp"

namespace Graphics3D {
  class ProgramOpenGL {
  public:
    using Ptr = std::shared_ptr<ProgramOpenGL>;
  
    ProgramOpenGL(ProgType);
    ProgramOpenGL(const ProgramOpenGL &) = delete;
    ProgramOpenGL(ProgramOpenGL &&);
    ~ProgramOpenGL();
    
    ProgramOpenGL &operator=(const ProgramOpenGL &) = delete;
    ProgramOpenGL &operator=(ProgramOpenGL &&);
    
    void load();
    
    void bind() const;
    void unbind() const;
    bool isBound() const;
    
    GLuint getID() const;
  private:
    GLuint id;
    bool linkOK = false;
    ProgType type;
    
    GLuint attach(const Res::ID &);
    void link();
    void printInfoLog();
    std::string getName() const;
    
    static GLuint bound;
  };
}

#endif

#endif
