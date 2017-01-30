//
//  attribs.hpp
//  Game Engine
//
//  Created by Indi Kernick on 30/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_opengl_attribs_hpp
#define engine_3d_opengl_attribs_hpp

#ifdef USE_OPENGL

#include "attrib pointer.hpp"
#include "constants.hpp"

namespace Graphics3D {
  //using function references causes a duplicate symbol error
  constexpr auto *enablePos = &enable<POS_LOC>;
  constexpr auto *enableNormal = &enable<NORM_LOC>;
  constexpr auto *enableTexturePos = &enable<TEX_POS_LOC>;
  constexpr auto *enableBoneID = &enableArray<BONE_ID_LOC, MAX_BONES_PER_VERTEX>;
  constexpr auto *enableBoneWeight = &enableArray<BONE_WGHT_LOC, MAX_BONES_PER_VERTEX>;
  
  constexpr auto *disablePos = &disable<POS_LOC>;
  constexpr auto *disableNormal = &disable<NORM_LOC>;
  constexpr auto *disableTexturePos = &disable<TEX_POS_LOC>;
  constexpr auto *disableBoneID = &disableArray<BONE_ID_LOC, MAX_BONES_PER_VERTEX>;
  constexpr auto *disableBoneWeight = &disableArray<BONE_WGHT_LOC, MAX_BONES_PER_VERTEX>;

  constexpr auto *posPointer = &attribPointer<GLfloat[3], POS_LOC>;
  constexpr auto *normalPointer = &attribPointer<GLfloat[3], NORM_LOC>;
  constexpr auto *texturePosPointer = &attribPointer<GLfloat[2], TEX_POS_LOC>;
  constexpr auto *boneIDPointer = &attribPointerArray<GLuint, BONE_ID_LOC, MAX_BONES_PER_VERTEX>;
  constexpr auto *boneWeightPointer = &attribPointerArray<GLfloat, BONE_WGHT_LOC, MAX_BONES_PER_VERTEX>;
}

#endif

#endif
