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
  
  constexpr GLuint LIGHT_DIRECT = 0;
  constexpr GLuint LIGHT_SPHERE = 1;
  constexpr GLuint LIGHT_CIRC_SPOT = 2;
  constexpr GLuint LIGHT_RECT_SPOT = 3;

  constexpr GLint POS_LOC = 0;
  constexpr GLint POS_2D_LOC = 1;
  constexpr GLint NORM_LOC = 2;
  constexpr GLint TEX_POS_LOC = 3;
  constexpr GLint BONE_ID_LOC = 4;
  constexpr GLint BONE_WGHT_LOC = BONE_ID_LOC + MAX_BONES_PER_VERTEX;
  
  constexpr size_t POS_SIZE = 3 * sizeof(GLfloat);
  constexpr size_t POS_2D_SIZE = 2 * sizeof(GLfloat);
  constexpr size_t NORM_SIZE = 3 * sizeof(GLfloat);
  constexpr size_t TEX_POS_SIZE = 2 * sizeof(GLfloat);
  constexpr size_t BONE_ID_SIZE = MAX_BONES_PER_VERTEX * sizeof(GLuint);
  constexpr size_t BONE_WGHT_SIZE = MAX_BONES_PER_VERTEX * sizeof(GLfloat);
}

#endif

#endif
