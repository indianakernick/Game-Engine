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
#include "types.hpp"

namespace UI {
  class AABBStack final : public OpStack<Bounds, AABB> {
  public:
    explicit AABBStack(float);
    ~AABBStack() = default;
  
    void setAspect(float);
    
  private:
    float screenAspect;
    
    Bounds operation(const Bounds &, const AABB &) override;
    
    glm::vec2 calcRelSize(const AABB &, Bounds) const;
    glm::vec2 calcAbsSize(const AABB &) const;
    glm::vec2 calcOriginDelta(Origin, glm::vec2) const;
    glm::vec2 calcRelParentOriginDelta(Origin, Bounds) const;
    glm::vec2 calcAbsParentOriginDelta(Origin) const;
  };
};

#endif
