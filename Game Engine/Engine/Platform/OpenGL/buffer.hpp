//
//  buffer.hpp
//  Game Engine
//
//  Created by Indi Kernick on 8/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_platform_opengl_buffer_hpp
#define engine_platform_opengl_buffer_hpp

#ifdef USE_OPENGL

#include "opengl.hpp"

namespace Platform {
  class Bind {};
  
  static constexpr Bind BIND {};

  template <GLenum TARGET>
  class Buffer {
  public:
    Buffer() {
      glGenBuffers(1, &id);
    }
    Buffer(Bind) {
      glGenBuffers(1, &id);
      glBindBuffer(TARGET, id);
      CHECK_OPENGL_ERROR();
    }
    Buffer(const Buffer &) = delete;
    Buffer(Buffer &&other)
      : id(other.id) {
      other.id = 0;
    }
    ~Buffer() {
      glDeleteBuffers(1, &id);
    }
    
    Buffer &operator=(const Buffer &) = delete;
    Buffer &operator=(Buffer &&other) {
      glDeleteBuffers(1, &id);
      id = other.id;
      other.id = 0;
      return *this;
    }
    
    void bind() {
      glBindBuffer(TARGET, id);
      CHECK_OPENGL_ERROR();
    }
    
  private:
    GLuint id;
  };
  
  using ArrayBuffer = Buffer<GL_ARRAY_BUFFER>;
  using ElementBuffer = Buffer<GL_ELEMENT_ARRAY_BUFFER>;
  
  class VertexArray {
  public:
    VertexArray();
    VertexArray(Bind);
    VertexArray(const VertexArray &) = delete;
    VertexArray(VertexArray &&);
    ~VertexArray();
    
    VertexArray &operator=(const VertexArray &) = delete;
    VertexArray &operator=(VertexArray &&);
    
    void bind();
  
  private:
    GLuint id;
  };
}

#endif

#endif
