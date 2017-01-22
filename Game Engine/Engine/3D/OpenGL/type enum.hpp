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

namespace Graphics3D {
  template <typename T>
  struct TypeEnum {};
  
  ///GLboolean is defined as a uint8_t so the types conflict
  template <>
  struct TypeEnum<bool> {
    static const GLenum value = GL_BOOL;
  };
  
  template <>
  struct TypeEnum<GLbyte> {
    static const GLenum value = GL_BYTE;
  };
  
  template <>
  struct TypeEnum<GLubyte> {
    static const GLenum value = GL_UNSIGNED_BYTE;
  };
  
  template <>
  struct TypeEnum<GLshort> {
    static const GLenum value = GL_SHORT;
  };
  
  template <>
  struct TypeEnum<GLushort> {
    static const GLenum value = GL_UNSIGNED_SHORT;
  };
  
  template <>
  struct TypeEnum<GLint> {
    static const GLenum value = GL_INT;
  };
  
  template <>
  struct TypeEnum<GLuint> {
    static const GLenum value = GL_UNSIGNED_INT;
  };
  
  template <>
  struct TypeEnum<GLfloat> {
    static const GLenum value = GL_FLOAT;
  };
  
  template <>
  struct TypeEnum<GLdouble> {
    static const GLenum value = GL_DOUBLE;
  };
}

#endif

#endif
