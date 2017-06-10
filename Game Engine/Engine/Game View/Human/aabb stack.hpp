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
  class AABBStack final : public Utils::OpStack<Bounds, AABB> {
  public:
    explicit AABBStack(Coord);
    ~AABBStack() = default;
  
    void setAspect(Coord);
    
  private:
    Coord screenAspect;
    
    Bounds operation(const Bounds &, const AABB &) override;
    
    Point calcRelSize(const AABB &, Bounds) const;
    Point calcAbsSize(const AABB &) const;
    Point calcOriginDelta(Origin, Point) const;
    Point calcRelParentOriginDelta(Origin, Bounds) const;
    Point calcAbsParentOriginDelta(Origin) const;
  };
};

#endif
