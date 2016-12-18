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
#include <vector>

namespace Graphics3D {
  class MatStack {
  public:
    explicit MatStack(size_t = 32);
    
    void push(const glm::mat4 &);
    void push(glm::mat4 &&);
    void pop();
    
    inline const glm::mat4 &top() const {
      return stack.top();
    }
    size_t size() const;
  private:
    //according to my benchmarks, vector is faster than deque (the default)
    using Container = std::vector<glm::mat4>;
    using Stack = std::stack<glm::mat4, Container>;
    Stack stack;
    
    //std::vector<>::reserve fails when dealing with const values
    //in the container. Is that a bug?
    
    //std::vector<const int> v;
    //v.reserve(12);
  };
}

#endif
