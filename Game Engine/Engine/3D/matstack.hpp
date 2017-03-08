//
//  matstack.hpp
//  Game Engine
//
//  Created by Indi Kernick on 15/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_matstack_hpp
#define engine_3d_matstack_hpp

#include "../Utils/op stack.hpp"

namespace Graphics3D {
  template <typename MAT>
  class MatStack : public OpStack<MAT> {
  public:
    MatStack(size_t capacity = 32)
      : OpStack<MAT>(capacity, {}) {}
  private:
    MAT operation(const MAT &prev, const MAT &next) {
      return next * prev;
    }
  };
}

#endif
