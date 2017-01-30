//
//  attrib pointer.hpp
//  Game Engine
//
//  Created by Indi Kernick on 30/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_opengl_attrib_pointer_hpp
#define engine_3d_opengl_attrib_pointer_hpp

#ifdef USE_OPENGL

#include "../../Application/opengl.hpp"
#include <type_traits>
#include "type enum.hpp"

namespace Graphics3D {
  #define IS_FLOAT \
    typename std::enable_if<\
      std::is_floating_point<\
        typename std::remove_all_extents<T>::type\
      >::value,\
      void\
    >::type * = nullptr
  
  #define IS_INT \
    typename std::enable_if<\
      std::is_integral<\
        typename std::remove_all_extents<T>::type\
      >::value,\
      void\
    >::type * = nullptr
  
  #define ATTR_PTR(attr, norm, stride) \
    glVertexAttribPointer(\
      attr,\
      TypeEnum<T>::size,\
      TypeEnum<T>::type,\
      norm,\
      stride,\
      reinterpret_cast<const void *>(offset)\
    )
  
  #define ATTR_I_PTR(attr, stride) \
    glVertexAttribIPointer(\
      attr,\
      TypeEnum<T>::size,\
      TypeEnum<T>::type,\
      stride,\
      reinterpret_cast<const void *>(offset)\
    )

  template <typename T,
            GLint ATTR,
            IS_FLOAT>
  static void attribPointer(size_t stride, size_t offset) {
    ATTR_PTR(ATTR, GL_FALSE, static_cast<GLsizei>(stride));
  }
  
  template <typename T,
            GLint ATTR,
            bool NORM = false,
            IS_INT>
  static void attribPointer(size_t stride, size_t offset) {
    //if constexpr (NORM) {
    if (NORM) {
      ATTR_PTR(ATTR, GL_TRUE, static_cast<GLsizei>(stride));
    } else {
      ATTR_I_PTR(ATTR, static_cast<GLsizei>(stride));
    }
  }
  
  template <typename T,
            GLint ATTR,
            GLsizei SIZE,
            IS_FLOAT>
  static void attribPointerArray(size_t stride, size_t offset) {
    static_assert(SIZE > 0, "Cannot have array of zero size");
    const GLsizei realStride = stride == 0
                             ? sizeof(T) * SIZE
                             : static_cast<GLsizei>(stride);
    for (GLint a = ATTR; a < ATTR + SIZE; a++) {
      ATTR_PTR(a, GL_FALSE, realStride);
      offset += sizeof(T);
    }
  }
  
  template <typename T,
            GLint ATTR,
            GLsizei SIZE,
            bool NORM = false,
            IS_INT>
  static void attribPointerArray(size_t stride, size_t offset) {
    static_assert(SIZE > 0, "Cannot have array of zero size");
    const GLsizei realStride = stride == 0
                             ? sizeof(T) * SIZE
                             : static_cast<GLsizei>(stride);
    if (NORM) {
      for (GLint a = ATTR; a < ATTR + SIZE; a++) {
        ATTR_PTR(a, GL_TRUE, realStride);
        offset += sizeof(T);
      }
    } else {
      for (GLint a = ATTR; a < ATTR + SIZE; a++) {
        ATTR_I_PTR(a, realStride);
        offset += sizeof(T);
      }
    }
    
    /*
    this is slower without constexpr if
    for (GLint a = ATTR; a < ATTR + SIZE; a++) {
      if constexpr (NORM) {
        ATTR_PTR(a, GL_TRUE, realStride);
      } else {
        ATTR_I_PTR(a, realStride);
      }
      offset += sizeof(T);
    }*/
  }
  
  #undef IS_FLOAT
  #undef IS_INT
  #undef ATTR_PTR
  #undef ATTR_I_PTR
}

#endif

#endif
