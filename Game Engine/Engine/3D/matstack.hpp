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
    ~MatStack();
    
    void push(const glm::mat4 &);
    void push(glm::mat4 &&);
    void pop();
    
    inline const glm::mat4 &top() const {
      return stack[topIndex];
    }
    size_t size() const;
  private:
    //my benchmarks say this is faster than vector because
    //im not calling ctors or dtors
    glm::mat4 *stack;
    size_t topIndex = 0;
    
    //std::vector<>::reserve fails when dealing with const values
    //in the container. Is that a bug?
    
    //std::vector<const int> v;
    //v.reserve(12);
  };
}

#endif
