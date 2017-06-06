//
//  input.cpp
//  Game Engine
//
//  Created by Indi Kernick on 19/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "input.hpp"

UI::Input::Input(std::weak_ptr<Platform::Window> window)
  : window(window) {
  mouseDownID = evtMan->addListener(
    memFunWrap(this, &Input::onMouseDown)
  );
  mouseUpID = evtMan->addListener(
    memFunWrap(this, &Input::onMouseUp)
  );
  mouseMoveID = evtMan->addListener(
    memFunWrap(this, &Input::onMouseMove)
  );
}

UI::Input::~Input() {
  evtMan->remListener(mouseDownID);
  evtMan->remListener(mouseUpID);
  evtMan->remListener(mouseMoveID);
}

void UI::Input::setRoot(Element::Ptr newRoot) {
  assert(newRoot);
  root = newRoot;
}

void UI::Input::unSetRoot() {
  root = nullptr;
}

void UI::Input::onMouseDown(const ::Input::MouseDown::Ptr event) {
  mouseDown = true;
  handleMouseDown(getFocused(event));
}

void UI::Input::onMouseUp(const ::Input::MouseUp::Ptr event) {
  mouseDown = false;
  handleMouseUp(getFocused(event));
}

void UI::Input::onMouseMove(const ::Input::MouseMove::Ptr event) {
  std::shared_ptr<Platform::Window> strongWindow = safeLock(window);
  if (strongWindow == safeLock(event->window)) {
    handleMouseMove(
      getFocused(event),
      fromPixels(event->pos, strongWindow->size()),
      fromPixels(event->delta, strongWindow->size())
    );
  } else {
    handleMouseMove(nullptr, {0.0f, 0.0f}, {0.0f, 0.0f});
  }
}

void UI::Input::handleMouseDown(Element::Ptr focused) {
  /*
  if an element is clicked on, that element will receive a mouse down event
  */
  
  downElement = focused;
  if (downElement) {
    downElement->dispatchEvent<MouseDown>();
  }
  lastFocused = focused;
}

void UI::Input::handleMouseUp(Element::Ptr focused) {
  /*
  if the mouse clicks on some element then moves to another element, then when
  the mouse goes up, the element the mouse originally clicked on will recieve
  the mouse up event and the new element the mouse is over will receive a
  mouse enter event
  */
  
  if (downElement) {
    downElement->dispatchEvent<MouseUp>(downElement == focused);
    if (focused && focused != downElement) {
      focused->dispatchEvent<MouseEnter>(false);
    }
    downElement = nullptr;
  }
  lastFocused = focused;
}

void UI::Input::handleMouseMove(Element::Ptr focused, Point pos, Point delta) {
  /*
  if the mouse has left one element and entered another element, they
  will both receive leave and enter events but if the mouse is down then only 
  the element that has been clicked on will receive enter and leave events
  */
  
  if (lastFocused != focused) {
    if (mouseDown) {
      if (downElement == focused) {
        downElement->dispatchEvent<MouseEnter>(true);
      } else {
        downElement->dispatchEvent<MouseLeave>(true);
      }
    } else {
      if (lastFocused) {
        lastFocused->dispatchEvent<MouseLeave>(false);
      }
      if (focused) {
        focused->dispatchEvent<MouseEnter>(false);
      }
    }
  }
  
  if (downElement) {
    triggerMouseMove(downElement, pos, delta);
  } else if (focused) {
    triggerMouseMove(focused, pos, delta);
  }
  
  lastFocused = focused;
}

void UI::Input::triggerMouseMove(
  Element::Ptr element,
  const Point pos,
  const Point delta
) {
  const AbsBounds absBounds = getAbsBounds(element);
  MouseMove::Ptr mouseMove = std::make_shared<MouseMove>();
  mouseMove->relPos = (pos - absBounds.thisBounds.p) / absBounds.thisBounds.s;
  mouseMove->relParPos = (pos - absBounds.parentBounds.p) / absBounds.parentBounds.s;
  mouseMove->absPos = pos;
  mouseMove->relDelta = delta / absBounds.thisBounds.s;
  mouseMove->relParDelta = delta / absBounds.parentBounds.s;
  mouseMove->absDelta = delta;
  mouseMove->down = mouseDown;
  element->dispatchEvent(mouseMove);
}

bool UI::Input::withinHitRegion(
  const Element::Ptr element,
  const Bounds bounds,
  const Point pos
) {
  if (!element->hasHitRegion()) {
    return true;
  }
  
  return pointInPolygon((pos - bounds.p) / bounds.s, element->getHitRegion());
}

UI::Input::AbsBounds UI::Input::getAbsBounds(Element::Ptr element) {
  std::shared_ptr<Platform::Window> strongWindow = safeLock(window);
  AABBStack aabbStack(Math::aspectRatio<Coord>(strongWindow->size()));
  return getAbsBoundsHelper(*element, aabbStack);
}

//climbs to the root and the climbs back down pushing the bounds along the way
UI::Input::AbsBounds UI::Input::getAbsBoundsHelper(
  Element &element,
  AABBStack &aabbStack
) {
  if (element.hasParent()) {
    getAbsBoundsHelper(element.getParent(), aabbStack);
  }
  const Bounds parentBounds = aabbStack.top();
  aabbStack.push(element.getBounds());
  return {aabbStack.top(), parentBounds};
}

template <typename T>
UI::Element::Ptr UI::Input::getFocused(const std::shared_ptr<T> event) {
  if (root == nullptr) {
    return nullptr;
  }
  
  std::shared_ptr<Platform::Window> strongWindow = safeLock(window);
  
  if (strongWindow == safeLock(event->window)) {
    const UI::PointPx windowSize = strongWindow->size();
    Element::Ptr focused;
    AABBStack aabbStack(Math::aspectRatio<Coord>(windowSize));
    HeightStack heightStack;
    Height lastHeight = std::numeric_limits<Height>::min();
    getTopElement(
      root,
      focused,
      lastHeight,
      fromPixels(event->pos, windowSize),
      aabbStack,
      heightStack
    );
    return focused;
  } else {
    return nullptr;
  }
}

void UI::Input::getTopElement(
  Element::Ptr parent,
  Element::Ptr &currentLastFocused,
  Height &lastHeight,
  const Point pos,
  AABBStack &aabbStack,
  HeightStack &heightStack
) {
  aabbStack.push(parent->getBounds());
  heightStack.push(parent->getHeight());
  
  if (!parent->getPassthrough() && aabbStack.top().encloses(pos)) {
    if (withinHitRegion(parent, aabbStack.top(), pos)) {
      const Height parentHeight = heightStack.top();
      if (parentHeight > lastHeight) {
        currentLastFocused = parent;
        lastHeight = parentHeight;
      }
    }
  }
  
  const Element::Children &children = parent->getChildren();
  if (!children.empty()) {
    for (auto e = children.begin(); e != children.end(); ++e) {
      getTopElement(*e, currentLastFocused, lastHeight, pos, aabbStack, heightStack);
    }
  }
  
  heightStack.pop();
  aabbStack.pop();
}
