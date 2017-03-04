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
#include <stack>

namespace UI {
  ///A very simple AABB. Pos is from screen TL to box TL and
  ///size is relative to screen
  struct SimpleAABB {
    glm::vec2 pos  = {0.0f, 0.0f};
    glm::vec2 size = {1.0f, 1.0f};
  };

  class AABBStack {
  public:
    AABBStack(float);
  
    void setAspect(float);
    
    void push(const AABB &);
    void pop();
    const SimpleAABB &top() const;
  private:
    std::stack<SimpleAABB> stack;
    float screenAspect;
    
    glm::vec2 calcNewSize(const AABB &, SimpleAABB) const;
    glm::vec2 calcOriginDelta(Origin, glm::vec2) const;
    glm::vec2 calcRelParentOriginDelta(Origin, SimpleAABB) const;
    glm::vec2 calcAbsParentOriginDelta(Origin) const;
  };
};

#endif
