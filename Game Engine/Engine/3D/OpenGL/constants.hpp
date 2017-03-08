//
//  constants.hpp
//  Game Engine
//
//  Created by Indi Kernick on 30/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_opengl_constants_hpp
#define engine_3d_opengl_constants_hpp

#ifdef USE_OPENGL

#include "../../Application/opengl.hpp"

namespace Graphics3D {
  //All these constants need to be kept in sync with the shaders
  //These are the only constants that need to be kept in sync with the shaders

  constexpr GLuint MAX_BONES = 128;
  constexpr GLuint MAX_BONES_PER_VERTEX = 4;
  constexpr GLuint MAX_LIGHTS = 16;
  constexpr GLuint MAX_HEIGHT = 1000;
  
  constexpr GLuint LIGHT_DIRECT = 0;
  constexpr GLuint LIGHT_POINT = 1;
  constexpr GLuint LIGHT_SPOT = 2;
  
  constexpr GLuint DIFF_TEX_UNIT = 0;
  constexpr GLuint AMBI_TEX_UNIT = 1;
  constexpr GLuint SPEC_TEX_UNIT = 2;
  
  constexpr GLint POS_LOC = 0;
  constexpr GLint POS_2D_LOC = 1;
  constexpr GLint NORM_LOC = 2;
  constexpr GLint TEX_LOC = 3;
  constexpr GLint BONE_ID_LOC = 4;
  constexpr GLint BONE_WGHT_LOC = BONE_ID_LOC + MAX_BONES_PER_VERTEX;
  
  using PosType = GLfloat[3];
  using Pos2DType = GLfloat[2];
  using NormType = GLfloat[3];
  using TexType = GLfloat[2];
  using BoneIDType = GLuint;
  using BoneWeightType = GLfloat;
  using ElemType = GLushort;
  
  constexpr size_t POS_SIZE = sizeof(PosType);
  constexpr size_t POS_2D_SIZE = sizeof(Pos2DType);
  constexpr size_t NORM_SIZE = sizeof(NormType);
  constexpr size_t TEX_SIZE = sizeof(TexType);
  constexpr size_t BONE_ID_SIZE = MAX_BONES_PER_VERTEX * sizeof(BoneIDType);
  constexpr size_t BONE_WGHT_SIZE = MAX_BONES_PER_VERTEX * sizeof(BoneWeightType);
  constexpr size_t ELEM_SIZE = sizeof(ElemType);
  
  ///The same as the aiShadingMode enum from ASSIMP
  enum class FragType : uint8_t {
    SOLID,
    PHONG,
    BLINN,
    COOK_TORRANCE,
    TOON,
    OREN_NAYER,
    MINNAERT,
    FRESNEL,
    
    _COUNT = 4
  };
  
  struct ProgType {
    bool anim;
    FragType frag;
    bool ui = false;
  };
  
  //uniform locations
  
  constexpr GLint MVP_LOC = 0;
  constexpr GLint MODEL_LOC = 1;
  constexpr GLint TRANS_INV_MODEL_LOC = 2;
  constexpr GLint CAM_POS_LOC = 3;
  
  //material
  
  constexpr GLint DIFFUSE_LOC = 4;
  constexpr GLint AMBIENT_LOC = 5;
  constexpr GLint SPECULAR_LOC = 6;
  constexpr GLint SHININESS_LOC = 7;
  constexpr GLint DIFF_TEX_LOC = 8;
  constexpr GLint AMBI_TEX_LOC = 9;
  constexpr GLint SPEC_TEX_LOC = 10;
  
  //lights
  
  constexpr GLint L_TYPE_LOC      = 11 + MAX_LIGHTS * 0;
  constexpr GLint L_DIFF_LOC      = 11 + MAX_LIGHTS * 1;
  constexpr GLint L_AMBI_LOC      = 11 + MAX_LIGHTS * 2;
  constexpr GLint L_SPEC_LOC      = 11 + MAX_LIGHTS * 3;
  constexpr GLint L_INTENSITY_LOC = 11 + MAX_LIGHTS * 4;
  constexpr GLint L_ANGLE_LOC     = 11 + MAX_LIGHTS * 5;
  constexpr GLint L_POS_LOC       = 11 + MAX_LIGHTS * 6;
  constexpr GLint L_DIR_LOC       = 11 + MAX_LIGHTS * 7;
  constexpr GLint L_NUM_LOC       = 11 + MAX_LIGHTS * 8;
  
  constexpr GLint BONES_LOC = L_NUM_LOC + 1;
}

#endif

#endif
