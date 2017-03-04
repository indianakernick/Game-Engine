//
//  aabb stack.cpp
//  Game Engine
//
//  Created by Indi Kernick on 4/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "aabb stack.hpp"

UI::AABBStack::AABBStack(float aspect)
  : screenAspect(aspect) {
  assert(screenAspect > 0.0f);
  stack.emplace();
}

void UI::AABBStack::setAspect(float aspect) {
  screenAspect = aspect;
  assert(screenAspect > 0.0f);
}

void UI::AABBStack::push(const AABB &box) {
  SimpleAABB newTop;
  const SimpleAABB topBox = stack.top();
  
  newTop.size = calcNewSize(box, topBox);
  newTop.pos = calcOriginDelta(box.origin, newTop.size);
  
  if (box.posSpace == Space::REL) {
    newTop.pos += calcRelParentOriginDelta(box.parentOrigin, topBox);
    newTop.pos += box.pos * topBox.size;
  } else {
    newTop.pos += calcAbsParentOriginDelta(box.parentOrigin);
    newTop.pos += box.pos;
  }
  
  stack.emplace(newTop);
}

void UI::AABBStack::pop() {
  assert(stack.size() > 1);
  stack.pop();
}

const UI::SimpleAABB &UI::AABBStack::top() const {
  return stack.top();
}

glm::vec2 UI::AABBStack::calcNewSize(const AABB &box, SimpleAABB topBox) const {
  if (box.sizeSpace == Space::REL) {
    switch (box.propAxis) {
      case Axis::BOTH:
        return topBox.size * box.size;
      case Axis::HORI:
        return {topBox.size.x * box.size.x,
                topBox.size.x * box.size.y};
      case Axis::VERT:
        return {topBox.size.y * box.size.x,
                topBox.size.y * box.size.y};
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
