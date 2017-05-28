//
//  aabb stack.cpp
//  Game Engine
//
//  Created by Indi Kernick on 4/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "aabb stack.hpp"

UI::AABBStack::AABBStack(Coord aspect)
  : OpStack(32, {}), screenAspect(aspect) {
  assert(screenAspect > 0.0f);
}

void UI::AABBStack::setAspect(Coord aspect) {
  screenAspect = aspect;
  assert(screenAspect > 0.0f);
}

UI::Bounds UI::AABBStack::operation(const Bounds &prev, const AABB &next) {
  Bounds newTop;
  
  //When the stack is empty, the element being pushed is the root element
  //which should be relative to the screen because it has no parent
  if (next.sizeSpace() == Space::REL && !empty()) {
    newTop.s = calcRelSize(next, prev);
  } else {
    newTop.s = calcAbsSize(next);
  }
  
  newTop.p = calcOriginDelta(next.thisOrigin(), newTop.s);
  
  if (next.posSpace() == Space::REL && !empty()) {
    newTop.p += calcRelParentOriginDelta(next.parentOrigin(), prev);
    newTop.p += next.pos() * prev.s;
  } else {
    newTop.p += calcAbsParentOriginDelta(next.parentOrigin());
    newTop.p += next.pos();
  }
  
  return newTop;
}

//calcResSize and calcAbsSize are too similar. One must call the other somehow
//...
//hmm
//...

UI::Point UI::AABBStack::calcRelSize(const AABB &box, Bounds topBox) const {
  switch (box.sizeAxis()) {
    case Axis::BOTH:
      return box.size() * topBox.s;
    case Axis::HORI:
      return {
        box.width() * topBox.s.x,
        box.height() * screenAspect * topBox.s.x
      };
    case Axis::VERT:
      return {
        box.width() / screenAspect * topBox.s.y,
        box.height() * topBox.s.y
      };
    case Axis::MAX:
    case Axis::MIN:
      if (topBox.s.x < topBox.s.y && box.sizeAxis() == Axis::MIN) {
        return {
          box.width() * topBox.s.x,
          box.height() * screenAspect * topBox.s.x
        };
      } else {
        return {
          box.width() / screenAspect * topBox.s.y,
          box.height() * topBox.s.y
        };
      }
  }
}

UI::Point UI::AABBStack::calcAbsSize(const AABB &box) const {
  switch (box.sizeAxis()) {
    case Axis::BOTH:
      return box.size();
    case Axis::HORI:
      return {
        box.width(),
        box.height() * screenAspect
      };
    case Axis::VERT:
      return {
        box.width() / screenAspect,
        box.height()
      };
    case Axis::MAX:
    case Axis::MIN:
      if (box.width() < box.height() && box.sizeAxis() == Axis::MIN) {
        return {
          box.width(),
          box.height() * screenAspect
        };
      } else {
        return {
          box.width() / screenAspect,
          box.height()
        };
      }
  }
}

UI::Point UI::AABBStack::calcOriginDelta(Origin origin, Point newSize) const {
  return -newSize * calcAbsParentOriginDelta(origin);
}

UI::Point UI::AABBStack::calcRelParentOriginDelta(Origin origin, Bounds topBox) const {
  return topBox.p + topBox.s * calcAbsParentOriginDelta(origin);
}

UI::Point UI::AABBStack::calcAbsParentOriginDelta(Origin origin) const {
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
