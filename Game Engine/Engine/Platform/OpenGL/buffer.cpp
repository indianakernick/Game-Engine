//
//  buffer.cpp
//  Game Engine
//
//  Created by Indi Kernick on 8/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "buffer.hpp"

#ifdef USE_OPENGL

using namespace Platform;

Buffer::Buffer() {
  glGenBuffers(1, &id);
  CHECK_OPENGL_ERROR();
}

Buffer::Buffer(Bind, GLenum target) {
  glGenBuffers(1, &id);
  glBindBuffer(target, id);
  CHECK_OPENGL_ERROR();
}

Buffer::Buffer(Buffer &&other)
  : id(other.id) {
  other.id = 0;
}

Buffer::~Buffer() {
  glDeleteBuffers(1, &id);
}

Buffer &Buffer::operator=(Buffer &&other) {
  glDeleteBuffers(1, &id);
  id = other.id;
  other.id = 0;
  CHECK_OPENGL_ERROR();
  return *this;
}

void Buffer::bind(GLenum target) {
  glBindBuffer(target, id);
  CHECK_OPENGL_ERROR();
}

VertexArray::VertexArray() {
  glGenVertexArrays(1, &id);
  CHECK_OPENGL_ERROR();
}

VertexArray::VertexArray(Bind) {
  glGenVertexArrays(1, &id);
  glBindVertexArray(id);
  CHECK_OPENGL_ERROR();
}

VertexArray::VertexArray(VertexArray &&other)
  : id(other.id) {
  other.id = 0;
}

VertexArray::~VertexArray() {
  glDeleteVertexArrays(1, &id);
}

VertexArray &VertexArray::operator=(VertexArray &&other) {
  glDeleteVertexArrays(1, &id);
  id = other.id;
  other.id = 0;
  CHECK_OPENGL_ERROR();
  return *this;
}

void VertexArray::bind() {
  glBindVertexArray(id);
  CHECK_OPENGL_ERROR();
}

#endif
