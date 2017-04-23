//
//  aabb stack.hpp
//  Game Engine
//
//  Created by Indi Kernick on 4/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_game_view_human_aabb_stack_hpp
#define engine_game_view_human_aabb_stack_hpp

#include "aabb.hpp"
#include "../../Utils/op stack.hpp"

namespace UI {
  ///A very simple AABB. Pos is from screen TL to box TL and
  ///size is relative to screen
  struct SimpleAABB {
    glm::vec2 pos  = {0.0f, 0.0f};
    glm::vec2 size = {1.0f, 1.0f};
  };
  
  bool posWithinBounds(glm::vec2, const SimpleAABB &);
  
  class AABBStack final : public OpStack<SimpleAABB, AABB> {
  public:
    explicit AABBStack(float);
    ~AABBStack() = default;
  
    void setAspect(float);
    
  private:
    float screenAspect;
    
    SimpleAABB operation(const SimpleAABB &, const AABB &) override;
    
    glm::vec2 calcRelSize(const AABB &, SimpleAABB) const;
    glm::vec2 calcAbsSize(const AABB &) const;
    glm::vec2 calcOriginDelta(Origin, glm::vec2) const;
    glm::vec2 calcRelParentOriginDelta(Origin, SimpleAABB) const;
    glm::vec2 calcAbsParentOriginDelta(Origin) const;
  };
};

#endif
