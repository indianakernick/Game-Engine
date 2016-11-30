//
//  matstack.hpp
//  Game Engine
//
//  Created by Indi Kernick on 15/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_matstack_hpp
#define engine_3d_matstack_hpp

#include <glm/mat4x4.hpp>
#include <stack>

class MatStack {
public:
  MatStack();
  
  size_t push(const glm::mat4 &);
  size_t pop();
  
  inline const glm::mat4 &top() const {
    return stack.top();
  }
  size_t size() const;
private:
  std::stack<const glm::mat4> stack;
  static const size_t RESERVE = 20;
};

#endif
