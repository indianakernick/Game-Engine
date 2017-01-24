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
  template <typename T, bool ARRAY = (std::is_array<T>::value && std::extent<T>::value > 4)>
  struct TypeEnum {};
  
  template <typename T>
  struct TypeEnum<T, true> {
    static const GLenum scalarType =
      TypeEnum<typename std::remove_all_extents<T>::type, 0>::type;
    static const GLuint size = std::extent<T>::value;
  };
  
  #define TYPE_ENUM(wholeType, enum) \
  template <>\
  struct TypeEnum<wholeType, false> {\
    static const GLenum type = enum;\
    static const GLenum scalarType = \
      TypeEnum<typename std::remove_all_extents<wholeType>::type>::type;\
    static const GLuint size = std::is_array<wholeType>::value\
                               ? std::extent<wholeType>::value\
                               : 1;\
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
  
  TYPE_ENUM(bool[2], GL_BOOL_VEC2)
  TYPE_ENUM(GLbyte[2], GL_2_BYTES)
  TYPE_ENUM(GLint[2], GL_INT_VEC2)
  TYPE_ENUM(GLuint[2], GL_UNSIGNED_INT_VEC2)
  TYPE_ENUM(GLfloat[2], GL_FLOAT_VEC2)
  TYPE_ENUM(GLdouble[2], GL_DOUBLE_VEC2)
  
  TYPE_ENUM(bool[3], GL_BOOL_VEC3)
  TYPE_ENUM(GLbyte[3], GL_3_BYTES)
  TYPE_ENUM(GLint[3], GL_INT_VEC3)
  TYPE_ENUM(GLuint[3], GL_UNSIGNED_INT_VEC3)
  TYPE_ENUM(GLfloat[3], GL_FLOAT_VEC3)
  TYPE_ENUM(GLdouble[3], GL_DOUBLE_VEC3)
  
  TYPE_ENUM(bool[4], GL_BOOL_VEC4)
  TYPE_ENUM(GLbyte[4], GL_4_BYTES)
  TYPE_ENUM(GLint[4], GL_INT_VEC4)
  TYPE_ENUM(GLuint[4], GL_UNSIGNED_INT_VEC4)
  TYPE_ENUM(GLfloat[4], GL_FLOAT_VEC4)
  TYPE_ENUM(GLdouble[4], GL_DOUBLE_VEC4)
  
  #undef TYPE_ENUM
}

#endif

#endif
