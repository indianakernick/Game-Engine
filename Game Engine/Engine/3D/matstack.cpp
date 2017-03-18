//
//  matstack.cpp
//  Game Engine
//
//  Created by Indi Kernick on 15/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "matstack.hpp"

Graphics3D::MatStack::MatStack(size_t capacity)
  : OpStack<glm::mat4>(capacity, {}) {}

glm::mat4 Graphics3D::MatStack::operation(const glm::mat4 &prev,
                                          const glm::mat4 &next) {
  return next * prev;
}
