//
//  aabb stack.cpp
//  Game Engine
//
//  Created by Indi Kernick on 4/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "aabb stack.hpp"

bool UI::posWithinBounds(glm::vec2 pos, const SimpleAABB &bounds) {
  return pos.x >= bounds.pos.x && pos.x <= bounds.pos.x + bounds.size.x &&
         pos.y >= bounds.pos.y && pos.y <= bounds.pos.y + bounds.size.y;
}

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
  
  //When the stack is empty, the element being pushed is the root element
  //which should be relative to the screen because it has no parent
  if (next.sizeSpace == Space::REL && !empty()) {
    newTop.size = calcRelSize(next, prev);
  } else {
    newTop.size = calcAbsSize(next);
  }
  
  newTop.pos = calcOriginDelta(next.origin, newTop.size);
  
  if (next.posSpace == Space::REL && !empty()) {
    newTop.pos += calcRelParentOriginDelta(next.parentOrigin, prev);
    newTop.pos += next.pos * prev.size;
  } else {
    newTop.pos += calcAbsParentOriginDelta(next.parentOrigin);
    newTop.pos += next.pos;
  }
  
  return newTop;
}

glm::vec2 UI::AABBStack::calcRelSize(const AABB &box, SimpleAABB topBox) const {
  switch (box.propAxis) {
    case Axis::BOTH:
      return box.size * topBox.size;
    case Axis::HORI:
      return box.size * topBox.size.x;
    case Axis::VERT:
      return box.size * topBox.size.y;
  }
}

glm::vec2 UI::AABBStack::calcAbsSize(const AABB &box) const {
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
