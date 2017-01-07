//
//  matstack.cpp
//  Game Engine
//
//  Created by Indi Kernick on 15/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "matstack.hpp"

Graphics3D::MatStack::MatStack(size_t capacity)
  : stack(new glm::mat4[capacity]) {
  //identity matrix on the base
  stack[0] = {};
}

Graphics3D::MatStack::~MatStack() {
  delete[] stack;
}

void Graphics3D::MatStack::push(const glm::mat4 &mat) {
  stack[topIndex + 1] = mat * stack[topIndex];
  ++topIndex;
}

void Graphics3D::MatStack::push(glm::mat4 &&mat) {
  stack[topIndex + 1] = mat * stack[topIndex];
  ++topIndex;
}

void Graphics3D::MatStack::pop() {
  assert(topIndex);
  --topIndex;
}

size_t Graphics3D::MatStack::size() const {
  return topIndex + 1;
}
