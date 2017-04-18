//
//  input.cpp
//  Game Engine
//
//  Created by Indi Kernick on 19/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "input.hpp"

UI::Input::Input() {
  mouseDownID = evtMan->addListener(
    ::Input::MouseDown::TYPE,
    memFun(this, &Input::onMouseDown)
  );
  mouseUpID = evtMan->addListener(
    ::Input::MouseUp::TYPE,
    memFun(this, &Input::onMouseUp)
  );
  mouseMoveID = evtMan->addListener(
    ::Input::MouseMove::TYPE,
    memFun(this, &Input::onMouseMove)
  );
}

UI::Input::~Input() {
  evtMan->remListener(::Input::MouseDown::TYPE, mouseDownID);
  evtMan->remListener(::Input::MouseUp::TYPE, mouseUpID);
  evtMan->remListener(::Input::MouseMove::TYPE, mouseMoveID);
}

void UI::Input::setRoot(Element::Ptr newRoot) {
  assert(newRoot);
  root = newRoot;
}

void UI::Input::unSetRoot() {
  root = nullptr;
}

void UI::Input::onMouseDown(const Game::Event::Ptr event) {
  mouseDown = true;
  handleMouseDown(getFocused<::Input::MouseDown>(event));
}

void UI::Input::onMouseUp(const Game::Event::Ptr event) {
  mouseDown = false;
  handleMouseUp(getFocused<::Input::MouseUp>(event));
}

void UI::Input::onMouseMove(const Game::Event::Ptr event) {
  handleMouseMove(getFocused<::Input::MouseMove>(event));
}

void UI::Input::handleMouseDown(Element::Ptr focused) {
  /*
  if an element is clicked on, that element will receive a mouse down event
  */
  
  downElement = focused;
  if (downElement) {
    downElement->onMouseDown();
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
    downElement->onMouseUp(downElement == focused);
    if (focused && focused != downElement) {
      focused->onMouseEnter(false);
    }
    downElement = nullptr;
  }
  lastFocused = focused;
}

void UI::Input::handleMouseMove(Element::Ptr focused) {
  /*
  if the mouse has left one element and entered another element, they
  will both receive leave and enter events but if the mouse is down then only 
  the element that has been clicked on will receive enter and leave events
  */
  
  if (lastFocused != focused) {
    if (mouseDown) {
      if (downElement == focused) {
        downElement->onMouseEnter(true);
      } else {
        downElement->onMouseLeave(true);
      }
    } else {
      if (lastFocused) {
        lastFocused->onMouseLeave(false);
      }
      if (focused) {
        focused->onMouseEnter(false);
      }
    }
  }
  lastFocused = focused;
}

bool UI::Input::withinHitRegion(Element::Ptr element,
                                const SimpleAABB &bounds,
                                glm::vec2 pos) {
  if (!element->hasHitRegion()) {
    return true;
  }
  
  //position of mouse relative to element
  const glm::vec2 relPos = {
    (pos.x - bounds.pos.x) / bounds.size.x,
    (pos.y - bounds.pos.y) / bounds.size.y
  };
  
  return pointInPolygon(relPos, element->getHitRegion());
}

template <typename T>
UI::Element::Ptr UI::Input::getFocused(const Game::Event::Ptr event) {
  //FIX ME
  const glm::ivec2 windowSize = {1280, 720};//app->window->size();
  return getFocused(
    getRelPos(Game::castEvent<T>(event)->pos, windowSize),
    Math::aspectRatio<float>(windowSize)
  );
}

glm::vec2 UI::Input::getRelPos(glm::ivec2 pos, glm::ivec2 windowSize) {
  return {
    static_cast<float>(pos.x) / windowSize.x,
    static_cast<float>(pos.y) / windowSize.y
  };
}

UI::Element::Ptr UI::Input::getFocused(glm::vec2 pos, float aspectRatio) {
  if (root == nullptr) {
    return nullptr;
  }
  
  Element::Ptr focused;
  AABBStack aabbStack(aspectRatio);
  HeightStack heightStack;
  getTopElement(
    root,
    focused,
    std::numeric_limits<Height>::min(),
    pos,
    aabbStack,
    heightStack
  );
  return focused;
}

void UI::Input::getTopElement(
  Element::Ptr parent,
  Element::Ptr &lastFocused,
  Height lastHeight,
  glm::vec2 pos,
  AABBStack &aabbStack,
  HeightStack &heightStack
) {
  aabbStack.push(parent->getBounds());
  heightStack.push(parent->getHeight());
  
  if (!parent->getPassthrough() && posWithinBounds(pos, aabbStack.top())) {
    if (withinHitRegion(parent, aabbStack.top(), pos)) {
      const Height parentHeight = heightStack.top();
      if (parentHeight > lastHeight) {
        lastFocused = parent;
        lastHeight = parentHeight;
      }
    }
  }
  
  const Element::Children &children = parent->getChildren();
  if (!children.empty()) {
    for (auto e = children.begin(); e != children.end(); ++e) {
      getTopElement(*e, lastFocused, lastHeight, pos, aabbStack, heightStack);
    }
  }
  
  heightStack.pop();
  aabbStack.pop();
}
