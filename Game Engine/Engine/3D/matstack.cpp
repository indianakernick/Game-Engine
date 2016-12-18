//
//  matstack.cpp
//  Game Engine
//
//  Created by Indi Kernick on 15/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "matstack.hpp"

Graphics3D::MatStack::MatStack(size_t capacity) {
  Container container;
  container.reserve(capacity);
  stack = Stack(container);
  //identity matrix on the base
  stack.emplace();
}

void Graphics3D::MatStack::push(const glm::mat4 &mat) {
  stack.emplace(stack.top() * mat);
}

void Graphics3D::MatStack::push(glm::mat4 &&mat) {
  stack.emplace(stack.top() * mat);
}

void Graphics3D::MatStack::pop() {
  //can't pop the base
  assert(stack.size() > 1);
  stack.pop();
}

size_t Graphics3D::MatStack::size() const {
  return stack.size();
}
