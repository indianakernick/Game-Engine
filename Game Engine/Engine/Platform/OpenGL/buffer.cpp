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

VertexArray::VertexArray() {
  glGenVertexArrays(1, &id);
}

VertexArray::VertexArray(Bind) {
  glGenVertexArrays(1, &id);
  glBindVertexArray(id);
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
  return *this;
}

void VertexArray::bind() {
  glBindVertexArray(id);
}

#endif
