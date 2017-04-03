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
#include <glm/mat4x4.hpp>

namespace Graphics3D {
  class MatStack final : public OpStack<glm::mat4> {
  public:
    explicit MatStack(size_t = 32);
  private:
    glm::mat4 operation(const glm::mat4 &, const glm::mat4 &) override;
  };
}

#endif
