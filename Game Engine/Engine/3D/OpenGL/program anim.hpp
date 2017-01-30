//
//  program anim.hpp
//  Game Engine
//
//  Created by Indi Kernick on 24/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_opengl_program_anim_hpp
#define engine_3d_opengl_program_anim_hpp

#ifdef USE_OPENGL

#include "program phong.hpp"

namespace Graphics3D {
  class AnimPhong : public Phong {
  public:
    AnimPhong(const char *name = "Anim");
    
    void load() override;
    
    void enableAll() override;
    void disableAll() override;
    
    void enableBones();
    void disableBones();
    
    void setBones(const std::vector<glm::mat4> &bones);
  private:
    GLint bones;
  };
}

#endif

#endif
