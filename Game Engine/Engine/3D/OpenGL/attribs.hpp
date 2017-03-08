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
  constexpr auto *enablePos2D = &enable<POS_2D_LOC>;
  constexpr auto *enableNormal = &enable<NORM_LOC>;
  constexpr auto *enableTexturePos = &enable<TEX_LOC>;
  constexpr auto *enableBoneID = &enableArray<BONE_ID_LOC, MAX_BONES_PER_VERTEX>;
  constexpr auto *enableBoneWeight = &enableArray<BONE_WGHT_LOC, MAX_BONES_PER_VERTEX>;
  
  constexpr auto *disablePos = &disable<POS_LOC>;
  constexpr auto *disablePos2D = &disable<POS_2D_LOC>;
  constexpr auto *disableNormal = &disable<NORM_LOC>;
  constexpr auto *disableTexturePos = &disable<TEX_LOC>;
  constexpr auto *disableBoneID = &disableArray<BONE_ID_LOC, MAX_BONES_PER_VERTEX>;
  constexpr auto *disableBoneWeight = &disableArray<BONE_WGHT_LOC, MAX_BONES_PER_VERTEX>;

  constexpr auto *posPointer = &attribPointer<PosType, POS_LOC>;
  constexpr auto *pos2DPointer = &attribPointer<Pos2DType, POS_2D_LOC>;
  constexpr auto *normalPointer = &attribPointer<NormType, NORM_LOC>;
  constexpr auto *texturePosPointer = &attribPointer<TexType, TEX_LOC>;
  constexpr auto *boneIDPointer = &attribPointerArray<BoneIDType, BONE_ID_LOC, MAX_BONES_PER_VERTEX>;
  constexpr auto *boneWeightPointer = &attribPointerArray<BoneWeightType, BONE_WGHT_LOC, MAX_BONES_PER_VERTEX>;
}

#endif

#endif
