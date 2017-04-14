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

VertexArray::VertexArray(NoGen)
  : id(0) {}

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
  assert(id);
  glBindVertexArray(id);
}

void VertexArray::gen() {
  assert(id == 0);
  glGenVertexArrays(1, &id);
}

void VertexArray::swap(VertexArray &other) {
  std::swap(id, other.id);
}

bool VertexArray::exists() const {
  return id != 0;
}

VertexArrays::VertexArrays(size_t size)
  : ids(size) {
  glGenVertexArrays(static_cast<GLsizei>(size), ids.data());
}

VertexArrays::VertexArrays(size_t size, NoGen)
  : ids(size, 0) {}

VertexArrays::VertexArrays(VertexArrays &&other)
  : ids(std::move(other.ids)) {}

VertexArrays::~VertexArrays() {
  glDeleteVertexArrays(static_cast<GLsizei>(ids.size()), ids.data());
}

VertexArrays &VertexArrays::operator=(VertexArrays &&other) {
  ids.swap(other.ids);
  return *this;
}

void VertexArrays::bind(size_t i) {
  assert(i < ids.size());
  glBindVertexArray(ids[i]);
  CHECK_OPENGL_ERROR();
}

void VertexArrays::swap(VertexArrays &other) {
  ids.swap(other.ids);
}

size_t VertexArrays::size() const {
  return ids.size();
}

bool VertexArrays::empty() const {
  return ids.empty();
}

bool VertexArrays::exists(size_t i) const {
  assert(i < ids.size());
  return ids[i] != 0;
}

#endif
