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

UI::SimpleAABB UI::AABBStack::operation(const SimpleAABB &prev, const AABB &next) {
  SimpleAABB newTop;
  
  newTop.size = calcNewSize(next, prev);
  newTop.pos = calcOriginDelta(next.origin, newTop.size);
  
  if (next.posSpace == Space::REL) {
    newTop.pos += calcRelParentOriginDelta(next.parentOrigin, prev);
    newTop.pos += next.pos * prev.size;
  } else {
    newTop.pos += calcAbsParentOriginDelta(next.parentOrigin);
    newTop.pos += next.pos;
  }
  
  return newTop;
}

glm::vec2 UI::AABBStack::calcNewSize(const AABB &box, SimpleAABB topBox) const {
  if (box.sizeSpace == Space::REL) {
    switch (box.propAxis) {
      case Axis::BOTH:
        return topBox.size * box.size;
      case Axis::HORI:
        return topBox.size.x * box.size;
      case Axis::VERT:
        return topBox.size.y * box.size;
    }
  } else {
    switch (box.propAxis) {
      case Axis::BOTH:
        return box.size;
      case Axis::HORI:
        return {box.size.x,
                box.size.y * screenAspect};
      case Axis::VERT:
        return {box.size.x / screenAspect,
                box.size.y};
    }
  }
}

glm::vec2 UI::AABBStack::calcOriginDelta(Origin origin, glm::vec2 newSize) const {
  return -newSize * calcAbsParentOriginDelta(origin);
}

glm::vec2 UI::AABBStack::calcRelParentOriginDelta(Origin origin, SimpleAABB topBox) const {
  return topBox.pos + topBox.size * calcAbsParentOriginDelta(origin);
}

glm::vec2 UI::AABBStack::calcAbsParentOriginDelta(Origin origin) const {
  switch (origin) {
    case Origin::TOP_LEFT:
      return {0.0f, 0.0f};
    case Origin::TOP_RIGHT:
      return {1.0f, 0.0f};
    case Origin::BOTTOM_RIGHT:
      return {1.0f, 1.0f};
    case Origin::BOTTOM_LEFT:
      return {0.0f, 1.0f};
    case Origin::CENTER:
      return {0.5f, 0.5f};
  }
}
