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
  namespace GLProgs {
    class Anim : public Phong {
    public:
      static const int MAX_BONES_PER_VERTEX = 4;
      static const int MAX_BONES = 128;
    
      Anim(const char *name = "Anim");
      
      void load() override;
      
      void enableAll() override;
      void disableAll() override;
      
      void enableBones();
      void disableBones();
      
      void boneIDPointer();
      void boneWeightPointer();
      
      void setBones(const std::vector<glm::mat4> &bones);
    private:
      GLint bones;
      GLint boneID, boneWeight;
    };
  }
}

#endif

#endif
