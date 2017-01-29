//
//  program.hpp
//  opengl
//
//  Created by Indi Kernick on 22/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_opengl_program_hpp
#define engine_3d_opengl_program_hpp

#ifdef USE_OPENGL

#include "../../Resource/Handles/opengl shader.hpp"
#include "../../Utils/logger.hpp"
#include "../../Resource/shorter namespace.hpp"
#include "../../Application/global resource cache.hpp"
#include "type enum.hpp"
#include "set uniform.hpp"
#include <array>

namespace Graphics3D {
  class ProgramOpenGL {
  public:
    ProgramOpenGL(const char *);
    ProgramOpenGL(const ProgramOpenGL &) = delete;
    virtual ~ProgramOpenGL();
    
    ProgramOpenGL &operator=(const ProgramOpenGL &) = delete;
    
    virtual void load() = 0;
    virtual void enableAll() = 0;
    virtual void disableAll() = 0;
    
    void link();
    
    void bind() const;
    void unbind() const;
    bool isBound() const;
    
    GLuint getID() const;
  protected:
    void attach(const std::string &path);
    void setupShaders(const std::string &vert, const std::string &frag);
    
    GLint getAttr(const char *);
    GLint getUniform(const char *);
    
    void enable(GLint);
    void disable(GLint);
    void enableArray(GLint, GLsizei);
    void disableArray(GLint, GLsizei);
    
    template <typename T,
              typename std::enable_if<
                std::is_floating_point<
                  typename std::remove_all_extents<T>::type
                >::value,
                void
              >::type * = nullptr>
    void attribPointer(GLint attr, size_t stride, size_t offset, bool normalize = false) {
      glVertexAttribPointer(
        attr,
        TypeEnum<T>::size,
        TypeEnum<T>::scalarType,
        normalize ? GL_TRUE : GL_FALSE,
        static_cast<GLsizei>(stride),
        reinterpret_cast<const void *>(offset)
      );
    }
    
    template <typename T,
              typename std::enable_if<
                std::is_integral<
                  typename std::remove_all_extents<T>::type
                >::value,
                void
              >::type * = nullptr>
    void attribPointer(GLint attr, size_t stride, size_t offset) {
      //calling the integer version
      glVertexAttribIPointer(
        attr,
        TypeEnum<T>::size,
        TypeEnum<T>::scalarType,
        static_cast<GLsizei>(stride),
        reinterpret_cast<const void *>(offset)
      );
    }
    
    template <typename T,
              typename std::enable_if<
                std::is_floating_point<
                  typename std::remove_all_extents<T>::type
                >::value,
                void
              >::type * = nullptr>
    void attribPointerArray(GLint attr, GLsizei size, size_t stride,
                            size_t offset, bool normalize = false) {
      assert(size > 0);
      const GLint endAttr = attr + size;
      const GLsizei realStride = stride == 0
                               ? sizeof(T) * size
                               : static_cast<GLsizei>(stride);
      const GLboolean norm = normalize ? GL_TRUE : GL_FALSE;
      for (GLint a = attr; a < endAttr; a++) {
        glVertexAttribPointer(
          a,
          TypeEnum<T>::size,
          TypeEnum<T>::scalarType,
          norm,
          realStride,
          reinterpret_cast<const void *>(offset)
        );
        offset += sizeof(T);
      }
    }
    
    template <typename T,
              typename std::enable_if<
                std::is_integral<
                  typename std::remove_all_extents<T>::type
                >::value,
                void
              >::type * = nullptr>
    void attribPointerArray(GLint attr, GLsizei size, size_t stride, size_t offset) {
      assert(size > 0);
      const GLint endAttr = attr + size;
      const GLsizei realStride = stride == 0
                               ? sizeof(T) * size
                               : static_cast<GLsizei>(stride);
      for (GLint a = attr; a < endAttr; a++) {
        glVertexAttribIPointer(
          a,
          TypeEnum<T>::size,
          TypeEnum<T>::scalarType,
          realStride,
          reinterpret_cast<const void *>(offset)
        );
        offset += sizeof(T);
      }
    }
    
    void printInfoLog();
  private:
    GLuint id;
    const char *name;
    bool linkStatus = false;
    
    static GLuint bound;
  };
}

#endif

#endif
