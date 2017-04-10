//
//  type enum.hpp
//  Game Engine
//
//  Created by Indi Kernick on 22/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_platform_opengl_type_enum_hpp
#define engine_platform_opengl_type_enum_hpp

#ifdef USE_OPENGL

#include "opengl.hpp"
#include <type_traits>

namespace Platform {
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
    static const GLenum type = TypeEnum<std::remove_all_extents_t<wholeType>>::type;\
    static const GLsizei size = std::extent<wholeType>::value;\
  };
  
  #define MATRIX_TYPE_ENUM(wholeType) \
  template <>\
  struct TypeEnum<wholeType> {\
    static const GLenum type = TypeEnum<std::remove_all_extents_t<wholeType>>::type;\
    static const GLsizei rows = std::extent<wholeType, 0>::value;\
    static const GLsizei cols = std::extent<wholeType, 1>::value;\
  };
  
  #define MULTI_VECTOR_TYPE_ENUM(size) \
  VECTOR_TYPE_ENUM(bool[size])\
  VECTOR_TYPE_ENUM(GLbyte[size])\
  VECTOR_TYPE_ENUM(GLubyte[size])\
  VECTOR_TYPE_ENUM(GLshort[size])\
  VECTOR_TYPE_ENUM(GLushort[size])\
  VECTOR_TYPE_ENUM(GLint[size])\
  VECTOR_TYPE_ENUM(GLuint[size])\
  VECTOR_TYPE_ENUM(GLfloat[size])\
  VECTOR_TYPE_ENUM(GLdouble[size])\
  
  #define MULTI_MATRIX_TYPE_ENUM(rows, cols) \
  MATRIX_TYPE_ENUM(GLfloat[rows][cols])\
  MATRIX_TYPE_ENUM(GLdouble[rows][cols])
  
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
  
  MULTI_VECTOR_TYPE_ENUM(2)
  MULTI_VECTOR_TYPE_ENUM(3)
  MULTI_VECTOR_TYPE_ENUM(4)
  
  MULTI_MATRIX_TYPE_ENUM(2, 2)
  MULTI_MATRIX_TYPE_ENUM(2, 3)
  MULTI_MATRIX_TYPE_ENUM(2, 4)
  MULTI_MATRIX_TYPE_ENUM(3, 2)
  MULTI_MATRIX_TYPE_ENUM(3, 3)
  MULTI_MATRIX_TYPE_ENUM(3, 4)
  MULTI_MATRIX_TYPE_ENUM(4, 2)
  MULTI_MATRIX_TYPE_ENUM(4, 3)
  MULTI_MATRIX_TYPE_ENUM(4, 4)
  
  #undef TYPE_ENUM
  #undef VECTOR_TYPE_ENUM
  #undef MATRIX_TYPE_ENUM
  #undef MULTI_VECTOR_TYPE_ENUM
  #undef MULTI_MATRIX_TYPE_ENUM
}

#endif

#endif
