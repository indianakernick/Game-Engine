//
//  matstack.hpp
//  Game Engine
//
//  Created by Indi Kernick on 15/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_matstack_hpp
#define engine_3d_matstack_hpp

#include <cstddef>
#include <glm/mat4x4.hpp>

namespace Graphics3D {
  template <typename MAT>
  class MatStack {
  public:
    explicit MatStack(size_t capacity = 32)
      : stack(new MAT[capacity]) {
      //identity matrix on the base
      stack[0] = {};
    }
    ~MatStack() {
      delete[] stack;
    }
    
    void push(const MAT &mat) {
      stack[topIndex + 1] = mat * stack[topIndex];
      ++topIndex;
    }
    void push(MAT &&mat) {
      stack[topIndex + 1] = mat * stack[topIndex];
      ++topIndex;
    }
    void pop() {
      assert(topIndex);
      --topIndex;
    }
    
    inline const MAT &top() const {
      return stack[topIndex];
    }
    size_t size() const {
      return topIndex + 1;
    }
  private:
    //my benchmarks say this is faster than vector because
    //im not calling ctors or dtors
    MAT *stack;
    size_t topIndex = 0;
  };
}

#endif
