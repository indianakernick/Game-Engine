//
//  set uniform.hpp
//  Game Engine
//
//  Created by Indi Kernick on 27/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_opengl_set_uniform_hpp
#define engine_3d_opengl_set_uniform_hpp

#ifdef USE_OPENGL

#include "../../Application/opengl.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include <array>

namespace Graphics3D {
  template <typename T>
  void setUniform(GLint location, const T &value);
  
  //vectors
  
  #define VEC(num, type, typeChar, ...)\
  template <>\
  inline void setUniform(GLint location, const type &value) {\
    glUniform##num##typeChar(location, __VA_ARGS__);\
  }
  
  #define VEC1(type, typeChar)\
  VEC(1, type, typeChar, value)
  #define VEC2(type, typeChar) \
  VEC(2, glm::tvec2<type>, typeChar, value.x, value.y)
  #define VEC3(type, typeChar) \
  VEC(3, glm::tvec3<type>, typeChar, value.x, value.y, value.z)
  #define VEC4(type, typeChar) \
  VEC(4, glm::tvec4<type>, typeChar, value.x, value.y, value.z, value.w)
  
  #define VEC_ALL(type, typeChar)\
  VEC1(type, typeChar)\
  VEC2(type, typeChar)\
  VEC3(type, typeChar)\
  VEC4(type, typeChar)
  
  VEC_ALL(bool, i)
  VEC_ALL(GLfloat, f)
  VEC_ALL(GLint, i)
  VEC_ALL(GLuint, ui)
  VEC_ALL(GLdouble, d)
  
  //matricies
  
  #define MAT(rows, columns, type, typeChar)\
  template <>\
  inline void setUniform(\
    GLint location,\
    const glm::tmat##rows##x##columns<type> &value) {\
    \
    glUniformMatrix##rows##x##columns##typeChar##v(\
      location, 1, GL_FALSE, glm::value_ptr(value)\
    );\
  }
  #define SQUARE_MAT(rows, type, typeChar)\
  template <>\
  inline void setUniform(\
    GLint location,\
    const glm::tmat##rows##x##rows<type> &value) {\
    \
    glUniformMatrix##rows##typeChar##v(\
      location, 1, GL_FALSE, glm::value_ptr(value)\
    );\
  }
  
  #define MAT_ALL(type, typeChar)\
  SQUARE_MAT(2, type, typeChar)\
  MAT(2, 3, type, typeChar)\
  MAT(2, 4, type, typeChar)\
  MAT(3, 2, type, typeChar)\
  SQUARE_MAT(3, type, typeChar)\
  MAT(3, 4, type, typeChar)\
  MAT(4, 2, type, typeChar)\
  MAT(4, 3, type, typeChar)\
  SQUARE_MAT(4, type, typeChar)
  
  MAT_ALL(GLfloat, f)
  MAT_ALL(GLdouble, d)
  
  //arrays of vectors
  
  template <typename T>
  void setUniformArrayPtr(GLint location, size_t count, const T *values);
  
  template <typename T>
  inline void setUniformArray(GLint location, const std::vector<T> &values) {
    setUniformArrayPtr<T>(location, values.size(), values.data());
  }
  
  template <typename T, size_t SIZE>
  inline void setUniformArray(GLint location, const std::array<T, SIZE> &values) {
    setUniformArrayPtr<T>(location, SIZE, values.data());
  }
  
  template <typename T, size_t SIZE>
  inline void setUniformArray(GLint location, const T (&values)[SIZE]) {
    setUniformArrayPtr<T>(location, SIZE, values);
  }
  
  #define VEC_ARRAY(num, type, typeChar, arg)\
  template <>\
  inline void setUniformArrayPtr(GLint location, size_t count,\
                                 const type *values) {\
    assert(count > 0);\
    assert(values != nullptr);\
    glUniform##num##typeChar##v(location, static_cast<GLsizei>(count), arg);\
  }
  
  #define VEC1_ARRAY(type, typeChar)\
  VEC_ARRAY(1, type, typeChar, values)
  #define VEC2_ARRAY(type, typeChar)\
  VEC_ARRAY(2, glm::tvec2<type>, typeChar, glm::value_ptr(values[0]))
  #define VEC3_ARRAY(type, typeChar)\
  VEC_ARRAY(3, glm::tvec3<type>, typeChar, glm::value_ptr(values[0]))
  #define VEC4_ARRAY(type, typeChar)\
  VEC_ARRAY(4, glm::tvec4<type>, typeChar, glm::value_ptr(values[0]))
  
  #define VEC_ARRAY_ALL(type, typeChar)\
  VEC1_ARRAY(type, typeChar)\
  VEC2_ARRAY(type, typeChar)\
  VEC3_ARRAY(type, typeChar)\
  VEC4_ARRAY(type, typeChar)
  
  VEC_ARRAY_ALL(GLfloat, f)
  VEC_ARRAY_ALL(GLint, i)
  VEC_ARRAY_ALL(GLuint, ui)
  VEC_ARRAY_ALL(GLdouble, d)
  
  //arrays of matricies
  
  #define MAT_ARRAY(rows, columns, type, typeChar)\
  template <>\
  inline void setUniformArrayPtr(\
    GLint location, size_t count,\
    const glm::tmat##rows##x##columns<type> *values) {\
    \
    assert(count > 0);\
    assert(values != nullptr);\
    glUniformMatrix##rows##x##columns##typeChar##v(\
      location, static_cast<GLsizei>(count), GL_FALSE, glm::value_ptr(values[0])\
    );\
  }
  #define SQUARE_MAT_ARRAY(rows, type, typeChar)\
  template <>\
  inline void setUniformArrayPtr(\
    GLint location, size_t count,\
    const glm::tmat##rows##x##rows<type> *values) {\
    \
    assert(count > 0);\
    assert(values != nullptr);\
    glUniformMatrix##rows##typeChar##v(\
      location, static_cast<GLsizei>(count), GL_FALSE, glm::value_ptr(values[0])\
    );\
  }
  
  #define MAT_ARRAY_ALL(type, typeChar)\
  SQUARE_MAT_ARRAY(2, type, typeChar)\
  MAT_ARRAY(2, 3, type, typeChar)\
  MAT_ARRAY(2, 4, type, typeChar)\
  MAT_ARRAY(3, 2, type, typeChar)\
  SQUARE_MAT_ARRAY(3, type, typeChar)\
  MAT_ARRAY(3, 4, type, typeChar)\
  MAT_ARRAY(4, 2, type, typeChar)\
  MAT_ARRAY(4, 3, type, typeChar)\
  SQUARE_MAT_ARRAY(4, type, typeChar)
  
  MAT_ARRAY_ALL(GLfloat, f)
  MAT_ARRAY_ALL(GLdouble, d)
  
  #undef VEC
  #undef VEC1
  #undef VEC2
  #undef VEC3
  #undef VEC4
  #undef VEC_ALL
  
  #undef MAT
  #undef SQUARE_MAT
  #undef MAT_ALL
  
  #undef VEC_ARRAY
  #undef VEC1_ARRAY
  #undef VEC2_ARRAY
  #undef VEC3_ARRAY
  #undef VEC4_ARRAY
  #undef VEC_ARRAY_ALL
  
  #undef MAT_ARRAY
  #undef SQUARE_MAT_ARRAY
  #undef MAT_ARRAY_ALL
}

#endif

#endif
