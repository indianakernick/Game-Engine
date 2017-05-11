//
//  aabb stack.cpp
//  Game Engine
//
//  Created by Indi Kernick on 4/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "aabb stack.hpp"

UI::AABBStack::AABBStack(float aspect)
  : OpStack(32, {}), screenAspect(aspect) {
  assert(screenAspect > 0.0f);
}

void UI::AABBStack::setAspect(float aspect) {
  screenAspect = aspect;
  assert(screenAspect > 0.0f);
}

UI::Bounds UI::AABBStack::operation(const Bounds &prev, const AABB &next) {
  Bounds newTop;
  
  //When the stack is empty, the element being pushed is the root element
  //which should be relative to the screen because it has no parent
  if (next.sizeSpace == Space::REL && !empty()) {
    newTop.s = calcRelSize(next, prev);
  } else {
    newTop.s = calcAbsSize(next);
  }
  
  newTop.p = calcOriginDelta(next.origin, newTop.s);
  
  if (next.posSpace == Space::REL && !empty()) {
    newTop.p += calcRelParentOriginDelta(next.parentOrigin, prev);
    newTop.p += next.pos * prev.s;
  } else {
    newTop.p += calcAbsParentOriginDelta(next.parentOrigin);
    newTop.p += next.pos;
  }
  
  return newTop;
}

//calcResSize and calcAbsSize are too similar. One must call the other somehow
//...
//hmm
//...

glm::vec2 UI::AABBStack::calcRelSize(const AABB &box, Bounds topBox) const {
  switch (box.propAxis) {
    case Axis::BOTH:
      return box.size * topBox.s;
    case Axis::HORI:
      return {
        box.size.x * topBox.s.x,
        box.size.y * screenAspect * topBox.s.x
      };
    case Axis::VERT:
      return {
        box.size.x / screenAspect * topBox.s.y,
        box.size.y * topBox.s.y
      };
    case Axis::MAX:
    case Axis::MIN:
      if (topBox.s.x < topBox.s.y && box.propAxis == Axis::MIN) {
        return {
          box.size.x * topBox.s.x,
          box.size.y * screenAspect * topBox.s.x
        };
      } else {
        return {
          box.size.x / screenAspect * topBox.s.y,
          box.size.y * topBox.s.y
        };
      }
  }
}

glm::vec2 UI::AABBStack::calcAbsSize(const AABB &box) const {
  switch (box.propAxis) {
    case Axis::BOTH:
      return box.size;
    case Axis::HORI:
      return {
        box.size.x,
        box.size.y * screenAspect
      };
    case Axis::VERT:
      return {
        box.size.x / screenAspect,
        box.size.y
      };
    case Axis::MAX:
    case Axis::MIN:
      if (box.size.x < box.size.y && box.propAxis == Axis::MIN) {
        return {
          box.size.x,
          box.size.y * screenAspect
        };
      } else {
        return {
          box.size.x / screenAspect,
          box.size.y
        };
      }
  }
}

glm::vec2 UI::AABBStack::calcOriginDelta(Origin origin, glm::vec2 newSize) const {
  return -newSize * calcAbsParentOriginDelta(origin);
}

glm::vec2 UI::AABBStack::calcRelParentOriginDelta(Origin origin, Bounds topBox) const {
  return topBox.p + topBox.s * calcAbsParentOriginDelta(origin);
}

glm::vec2 UI::AABBStack::calcAbsParentOriginDelta(Origin origin) const {
  switch (origin) {
    case Origin::TOP_LEFT:
      return {0.0f, 0.0f};
    case Origin::TOP:
      return {0.5f, 0.0f};
    case Origin::TOP_RIGHT:
      return {1.0f, 0.0f};
    case Origin::RIGHT:
      return {1.0f, 0.5f};
    case Origin::BOTTOM_RIGHT:
      return {1.0f, 1.0f};
    case Origin::BOTTOM:
      return {0.5f, 1.0f};
    case Origin::BOTTOM_LEFT:
      return {0.0f, 1.0f};
    case Origin::LEFT:
      return {0.0f, 0.5f};
    case Origin::CENTER:
      return {0.5f, 0.5f};
  }
}
