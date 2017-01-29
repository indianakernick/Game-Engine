//
//  type enum.hpp
//  Game Engine
//
//  Created by Indi Kernick on 22/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_opengl_type_enum_hpp
#define engine_3d_opengl_type_enum_hpp

#ifdef USE_OPENGL

#include "../../Application/opengl.hpp"
#include <type_traits>

namespace Graphics3D {
  template <typename T>
  struct TypeEnum {};
  
  #define TYPE_ENUM(wholeType, enum) \
  template <>\
  struct TypeEnum<wholeType> {\
    static const GLenum type = enum;\
    static const GLsizei size = 1;\
  };
  
  #define VECTOR_TYPE_ENUM(wholeType) \
  template <>\
  struct TypeEnum<wholeType> {\
    static const GLenum type = \
      TypeEnum<typename std::remove_all_extents<wholeType>::type>::type;\
    static const GLsizei size = std::extent<wholeType>::value;\
  };
  
  //GLboolean is defined as a uint8_t so the types conflict
  
  TYPE_ENUM(bool, GL_BOOL)
  TYPE_ENUM(GLbyte, GL_BYTE)
  TYPE_ENUM(GLubyte, GL_UNSIGNED_BYTE)
  TYPE_ENUM(GLshort, GL_SHORT)
  TYPE_ENUM(GLushort, GL_UNSIGNED_SHORT)
  TYPE_ENUM(GLint, GL_INT)
  TYPE_ENUM(GLuint, GL_UNSIGNED_INT)
  TYPE_ENUM(GLfloat, GL_FLOAT)
  TYPE_ENUM(GLdouble, GL_DOUBLE)
  
  VECTOR_TYPE_ENUM(bool[2]);
  VECTOR_TYPE_ENUM(GLbyte[2]);
  VECTOR_TYPE_ENUM(GLubyte[2]);
  VECTOR_TYPE_ENUM(GLshort[2]);
  VECTOR_TYPE_ENUM(GLushort[2]);
  VECTOR_TYPE_ENUM(GLint[2]);
  VECTOR_TYPE_ENUM(GLuint[2]);
  VECTOR_TYPE_ENUM(GLfloat[2]);
  VECTOR_TYPE_ENUM(GLdouble[2]);
  
  VECTOR_TYPE_ENUM(bool[3]);
  VECTOR_TYPE_ENUM(GLbyte[3]);
  VECTOR_TYPE_ENUM(GLubyte[3]);
  VECTOR_TYPE_ENUM(GLshort[3]);
  VECTOR_TYPE_ENUM(GLushort[3]);
  VECTOR_TYPE_ENUM(GLint[3]);
  VECTOR_TYPE_ENUM(GLuint[3]);
  VECTOR_TYPE_ENUM(GLfloat[3]);
  VECTOR_TYPE_ENUM(GLdouble[3]);
  
  VECTOR_TYPE_ENUM(bool[4]);
  VECTOR_TYPE_ENUM(GLbyte[4]);
  VECTOR_TYPE_ENUM(GLubyte[4]);
  VECTOR_TYPE_ENUM(GLshort[4]);
  VECTOR_TYPE_ENUM(GLushort[4]);
  VECTOR_TYPE_ENUM(GLint[4]);
  VECTOR_TYPE_ENUM(GLuint[4]);
  VECTOR_TYPE_ENUM(GLfloat[4]);
  VECTOR_TYPE_ENUM(GLdouble[4]);
  
  #undef TYPE_ENUM
}

#endif

#endif
