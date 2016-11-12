//
//  matstack.cpp
//  game engine
//
//  Created by Indi Kernick on 15/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "matstack.hpp"

MatStack::MatStack() {
  //std::stack doesn't have a reserve function so i have to do this
  for (size_t i = 0; i < RESERVE; i++) {
    stack.emplace();
  }
  for (size_t i = 0; i < RESERVE; i++) {
    stack.pop();
  }
  //identity matrix on the base
  stack.emplace();
}

size_t MatStack::push(const glm::mat4 &mat) {
  stack.emplace(const_cast<glm::mat4 &>(stack.top()) * mat);
  return stack.size();
}

size_t MatStack::pop() {
  //can't pop the base
  assert(stack.size() > 1);
  stack.pop();
  return stack.size();
}

size_t MatStack::size() const {
  return stack.size();
}