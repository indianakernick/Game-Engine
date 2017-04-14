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
#include <vector>

namespace Platform {
  class Bind {};
  constexpr Bind BIND {};
  
  class NoGen {};
  constexpr NoGen NO_GEN {};

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
    Buffer(NoGen)
      : id(0) {}
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
      assert(id);
      glBindBuffer(TARGET, id);
      CHECK_OPENGL_ERROR();
    }
    
    void gen() {
      assert(id == 0);
      glGenBuffers(1, &id);
    }
    
    void swap(Buffer &other) {
      std::swap(id, other.id);
    }
    
    bool exists() const {
      return id != 0;
    }
    
  private:
    GLuint id;
  };
  
  template <GLenum TARGET>
  class Buffers {
  public:
    Buffers() = default;
    Buffers(size_t size)
      : ids(size) {
      glGenBuffers(static_cast<GLsizei>(size), ids.data());
    }
    Buffers(size_t size, NoGen)
      : ids(size, 0) {}
    Buffers(const Buffers &) = delete;
    Buffers(Buffers &&other)
      : ids(std::move(other.ids)) {}
    ~Buffers() {
      glDeleteBuffers(static_cast<GLsizei>(ids.size()), ids.data());
    }
    
    Buffers &operator=(const Buffers &) = delete;
    Buffers &operator=(Buffers &&other) {
      ids.swap(other.ids);
      return *this;
    }
    
    void bind(size_t i) {
      assert(i < ids.size());
      assert(ids[i]);
      glBindBuffer(TARGET, ids[i]);
      CHECK_OPENGL_ERROR();
    }
    
    void gen(size_t i) {
      assert(i < ids.size());
      assert(ids[i] == 0);
      glGenBuffers(1, &ids[i]);
    }
    
    void swap(Buffers &other) {
      ids.swap(other.ids);
    }
    
    size_t size() const {
      return ids.size();
    }
    
    bool empty() const {
      return ids.empty();
    }
    
    bool exists(size_t i) const {
      assert(i < ids.size());
      return ids[i] != 0;
    }
    
  protected:
    std::vector<GLuint> ids;
  };
  
  using ArrayBuffer = Buffer<GL_ARRAY_BUFFER>;
  using ElementBuffer = Buffer<GL_ELEMENT_ARRAY_BUFFER>;
  
  using ArrayBuffers = Buffers<GL_ARRAY_BUFFER>;
  using ElementBuffers = Buffers<GL_ELEMENT_ARRAY_BUFFER>;
  
  class VertexArray {
  public:
    VertexArray();
    VertexArray(Bind);
    VertexArray(NoGen);
    VertexArray(const VertexArray &) = delete;
    VertexArray(VertexArray &&);
    ~VertexArray();
    
    VertexArray &operator=(const VertexArray &) = delete;
    VertexArray &operator=(VertexArray &&);
    
    void bind();
    void gen();
    void swap(VertexArray &);
    bool exists() const;
  
  private:
    GLuint id;
  };
  
  class VertexArrays {
  public:
    VertexArrays();
    VertexArrays(size_t);
    VertexArrays(size_t, NoGen);
    VertexArrays(const VertexArrays &) = delete;
    VertexArrays(VertexArrays &&);
    ~VertexArrays();
    
    VertexArrays &operator=(const VertexArrays &) = delete;
    VertexArrays &operator=(VertexArrays &&);
    
    void bind(size_t);
    void gen(size_t);
    void swap(VertexArrays &);
    size_t size() const;
    bool empty() const;
    bool exists(size_t) const;
  
  private:
    std::vector<GLuint> ids;
  };
}

#endif

#endif
