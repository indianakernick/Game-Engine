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
  template <GLint ATTR>
  void enable() {
    glEnableVertexAttribArray(ATTR);
  }
  template <GLint ATTR>
  void disable() {
    glDisableVertexAttribArray(ATTR);
  }
  
  template <GLint ATTR, typename T>
  void enableMat() {
    static_assert(std::rank<T>::value == 2, "Type must be a matrix (2D array)");
    //                                        columns
    for (GLint a = ATTR; a < ATTR + std::extent<T, 1>::value; a++) {
      glEnableVertexAttribArray(a);
    }
  }
  template <GLint ATTR, typename T>
  void disableMat() {
    static_assert(std::rank<T>::value == 2, "Type must be a matrix (2D array)");
    //                                        columns
    for (GLint a = ATTR; a < ATTR + std::extent<T, 1>::value; a++) {
      glDisableVertexAttribArray(a);
    }
  }
  
  template <GLint ATTR, GLsizei SIZE>
  void enableArray() {
    static_assert(SIZE > 0, "Cannot have array of zero size");
    for (GLint a = ATTR; a < ATTR + SIZE; a++) {
      glEnableVertexAttribArray(a);
    }
  }
  template <GLint ATTR, GLsizei SIZE>
  void disableArray() {
    static_assert(SIZE > 0, "Cannot have array of zero size");
    for (GLint a = ATTR; a < ATTR + SIZE; a++) {
      glDisableVertexAttribArray(a);
    }
  }
  
  template <GLint ATTR, GLsizei SIZE, typename T>
  void enableMatArray() {
    static_assert(SIZE > 0, "Cannot have array of zero size");
    static_assert(std::rank<T>::value == 2, "Type must be a matrix (2D array)");
    //                                               columns
    for (GLint a = ATTR; a < ATTR + SIZE * std::extent<T, 1>::value; a++) {
      glEnableVertexAttribArray(a);
    }
  }
  template <GLint ATTR, GLsizei SIZE, typename T>
  void disableMatArray() {
    static_assert(SIZE > 0, "Cannot have array of zero size");
    static_assert(std::rank<T>::value == 2, "Type must be a matrix (2D array)");
    //                                               columns
    for (GLint a = ATTR; a < ATTR + SIZE * std::extent<T, 1>::value; a++) {
      glDisableVertexAttribArray(a);
    }
  }

  #define IS_FLOAT \
    std::enable_if_t<\
      std::is_floating_point<std::remove_all_extents_t<T>>::value,\
      void\
    > * = nullptr
  
  #define IS_INT \
    std::enable_if_t<\
      std::is_integral<std::remove_all_extents_t<T>>::value,\
      void\
    > * = nullptr
  
  #define IS_MAT \
    std::enable_if_t<\
      std::rank<T>::value == 2,\
      void\
    > * = nullptr
  
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
  
  #define ATTR_PTR_MAT(attr, norm, stride) \
    glVertexAttribPointer(\
      attr,\
      TypeEnum<T>::rows,\
      TypeEnum<T>::type,\
      norm,\
      stride,\
      reinterpret_cast<const void *>(offset)\
    )
  
  #define ATTR_I_PTR_MAT(attr, stride) \
    glVertexAttribPointer(\
      attr,\
      TypeEnum<T>::rows,\
      TypeEnum<T>::type,\
      stride,\
      reinterpret_cast<const void *>(offset)\
    )


  template <typename T,
            GLint ATTR,
            IS_FLOAT>
  void attribPointer(size_t stride, size_t offset) {
    ATTR_PTR(ATTR, GL_FALSE, static_cast<GLsizei>(stride));
  }
  
  template <typename T,
            GLint ATTR,
            bool NORM = false,
            IS_INT>
  void attribPointer(size_t stride, size_t offset) {
    //if constexpr (NORM) {
    if (NORM) {
      ATTR_PTR(ATTR, GL_TRUE, static_cast<GLsizei>(stride));
    } else {
      ATTR_I_PTR(ATTR, static_cast<GLsizei>(stride));
    }
  }
  
  template <typename T,
            GLint ATTR,
            IS_FLOAT,
            IS_MAT>
  void attribPointer(size_t stride, size_t offset) {
    const GLsizei realStride = stride == 0
                             ? sizeof(T)
                             : static_cast<GLsizei>(stride);
    constexpr size_t COL_SIZE =
      TypeEnum<T>::rows * sizeof(std::remove_all_extents_t<T>);
    for (GLsizei c = 0; c < TypeEnum<T>::cols; c++) {
      ATTR_PTR_MAT(ATTR + c, GL_FALSE, realStride);
      offset += COL_SIZE;
    }
  }
  
  template <typename T,
            GLint ATTR,
            bool NORM = false,
            IS_INT,
            IS_MAT>
  void attribPointer(size_t stride, size_t offset) {
    const GLsizei realStride = stride == 0
                             ? sizeof(T)
                             : static_cast<GLsizei>(stride);
    constexpr size_t COL_SIZE =
      TypeEnum<T>::rows * sizeof(std::remove_all_extents_t<T>);
    for (GLsizei c = 0; c < TypeEnum<T>::cols; c++) {
      if (NORM) {
        ATTR_PTR_MAT(ATTR + c, GL_TRUE, realStride);
      } else {
        ATTR_I_PTR_MAT(ATTR + c, realStride);
      }
      offset += COL_SIZE;
    }
  }
  
  template <typename T,
            GLint ATTR,
            GLsizei SIZE,
            IS_FLOAT>
  void attribPointerArray(size_t stride, size_t offset) {
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
  void attribPointerArray(size_t stride, size_t offset) {
    static_assert(SIZE > 0, "Cannot have array of zero size");
    const GLsizei realStride = stride == 0
                             ? sizeof(T) * SIZE
                             : static_cast<GLsizei>(stride);
    for (GLint a = ATTR; a < ATTR + SIZE; a++) {
      if (NORM) {
        ATTR_PTR(a, GL_TRUE, realStride);
      } else {
        ATTR_I_PTR(a, realStride);
      }
      offset += sizeof(T);
    }
  }
  
  template <typename T,
            GLint ATTR,
            GLsizei SIZE,
            IS_FLOAT,
            IS_MAT>
  void attribPointerArray(size_t stride, size_t offset) {
    static_assert(SIZE > 0, "Cannot have array of zero size");
    const GLsizei realStride = stride == 0
                             ? sizeof(T) * SIZE
                             : static_cast<GLsizei>(stride);
    constexpr size_t COL_SIZE =
      TypeEnum<T>::rows * sizeof(std::remove_all_extents_t<T>);
    for (GLint a = ATTR; a < ATTR + SIZE * TypeEnum<T>::cols; a++) {
      ATTR_PTR_MAT(a, GL_FALSE, realStride);
      offset += COL_SIZE;
    }
  }
  
  template <typename T,
            GLint ATTR,
            GLsizei SIZE,
            bool NORM = false,
            IS_INT,
            IS_MAT>
  void attribPointerArray(size_t stride, size_t offset) {
    static_assert(SIZE > 0, "Cannot have array of zero size");
    const GLsizei realStride = stride == 0
                             ? sizeof(T) * SIZE
                             : static_cast<GLsizei>(stride);
    constexpr size_t COL_SIZE =
      TypeEnum<T>::rows * sizeof(std::remove_all_extents_t<T>);
    for (GLint a = ATTR; a < ATTR + SIZE * TypeEnum<T>::cols; a++) {
      if (NORM) {
        ATTR_PTR_MAT(a, GL_TRUE, realStride);
      } else {
        ATTR_I_PTR_MAT(a, realStride);
      }
      offset += COL_SIZE;
    }
  }
  
  #undef IS_FLOAT
  #undef IS_INT
  #undef ATTR_PTR
  #undef ATTR_I_PTR
  #undef ATTR_PTR_MAT
  #undef ATTR_I_PTR_MAT
}

#endif

#endif
