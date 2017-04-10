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

  class Buffer {
  public:
    Buffer();
    Buffer(Bind, GLenum);
    Buffer(const Buffer &) = delete;
    Buffer(Buffer &&);
    ~Buffer();
    
    Buffer &operator=(const Buffer &) = delete;
    Buffer &operator=(Buffer &&);
    
    void bind(GLenum);
    
  private:
    GLuint id;
  };
  
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
