//
//  element.cpp
//  Game Engine
//
//  Created by Indi Kernick on 13/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "element.hpp"

bool Element::isVisible() const {
  return visible;
}

void Element::setVisible(bool newVisible) {
  visible = newVisible;
}

void Element::show() {
  visible = true;
}

void Element::hide() {
  visible = false;
}

int Element::getOrder() const {
  return order;
}

void Element::setOrder(int newOrder) {
  if (order != newOrder) {
    order = newOrder;
    if (parent) {
      parent->childOrderChanged = true;
    }
  }
}

bool Element::hasFocus() const {
  return focused;
}

void Element::focus() {
  changeFocus(this);
}

Geometry::Rect Element::getBounds() const {
  return bounds;
}

Element::Ptr Element::getPtr() {
  for (auto i = parent->children.begin(); i != parent->children.end(); ++i) {
    if ((*i).get() == this) {
      return *i;
    }
  }
  //that doesnt make any sense
  throw std::runtime_error("Element is not a child of its parent");
}

bool Element::canHandleScroll(Geometry::Point) const {
  return false;
}

bool Element::draggable() const {
  return false;
}

bool Element::droppable(Element *) const {
  return false;
}

void Element::init() {
  onInit();
  for (auto i = children.begin(); i != children.end(); ++i) {
    (*i)->init();
  }
}

void Element::input() {
  dispatchEvents();
  for (auto i = children.begin(); i != children.end(); ++i) {
    (*i)->input();
  }
}

void Element::update(uint64_t delta) {
  onUpdate(delta);
  for (auto i = children.begin(); i != children.end(); ++i) {
    (*i)->update(delta);
  }
  
  checkOrderChange();
}

void Element::render(Geometry::Point pixelPos) {
  if (!visible) {
    return;
  }
  
  pixelPos = pixelPos + bounds.p;

  int lastOrder = -1;
  for (auto i = children.begin(); i != children.end(); ++i) {
    if (lastOrder < 0 && (*i)->order >= 0) {
      onRender(pixelPos);
    }
    (*i)->render(pixelPos);
    lastOrder = (*i)->order;
  }
}

void Element::quit() {
  //quit in reverse order to init
  for (auto i = children.rbegin(); i != children.rend(); ++i) {
    (*i)->quit();
  }
  onQuit();
}

void Element::changeFocus(Element *element) {
  getRoot()->elementWithFocus = element;
}

Element *Element::getFocus() {
  return getRoot()->elementWithFocus;
}

RootElement *Element::getRoot() {
  //effective c++ - item 3
  //non-const member functions should call const member functions
  return const_cast<RootElement *>(
    static_cast<const Element *>(this)->getRoot()
  );
}

const RootElement *Element::getRoot() const {
  Element *parentElement = dynamic_cast<Element *>(parent);
  if (parentElement) {//parent is an Element
    return parentElement->getRoot();
  } else {//parent is a RootElement
    return dynamic_cast<RootElement *>(parentElement);
  }
}

bool Element::propMouse(Input::Event::Ptr event) {
  int lastOrder = 1;
  for (auto i = children.rbegin(); i != children.rend(); ++i) {
    if (lastOrder >= 0 && (*i)->order < 0) {
      if (handleEvent(event)) {
        return true;
      }
    }
    if ((*i)->propMouse(event)) {
      return true;
    }
    lastOrder = (*i)->order;
  }
  return false;
}

void Element::propResize(std::shared_ptr<Events::WindowResize> event) {
  pushEvent(event);
  for (auto i = children.begin(); i != children.end(); ++i) {
    (*i)->propResize(event);
  }
}

#define HANDLE(name) return handle##name(std::dynamic_pointer_cast<Input::name>(event));

bool Element::handleEvent(Input::Event::Ptr event) {
  switch (event->getType()) {
    case Input::MOUSE_DOWN:
      HANDLE(MouseDown)
    case Input::MOUSE_UP:
      HANDLE(MouseUp)
    case Input::MOUSE_MOVE:
      HANDLE(MouseMove)
    case Input::SCROLL:
      HANDLE(Scroll)
    default:
      //this code shouldn't run
      assert(false);
  }
}

bool Element::handleMouseDown(std::shared_ptr<Input::MouseDown> event) {
  if (absToRelParent(event->pos).within(bounds)) {
    RootElement *root = getRoot();
    root->mouseDownPos = event->pos;
    root->mouseDownButton = event->button;
    root->mouseDownElement = this;
    
    auto mouseDownEvent = std::make_shared<Events::MouseDown>();
    mouseDownEvent->pos = absToRel(event->pos);
    mouseDownEvent->which = event->button;
    pushEvent(mouseDownEvent);
    return true;
  } else {
    return false;
  }
}

bool Element::handleMouseUp(std::shared_ptr<Input::MouseUp> event) {
  if (absToRelParent(event->pos).within(bounds)) {
    auto mouseUp = std::make_shared<Events::MouseUp>();
    mouseUp->pos = absToRel(event->pos);
    mouseUp->which = event->button;
    return true;
  } else {
    return false;
  }
}

bool Element::handleMouseMove(std::shared_ptr<Input::MouseMove> event) {
  RootElement *root = getRoot();
  
  Geometry::Point relParent = absToRelParent(event->pos);
  Geometry::Point prevPos = relParent - event->delta;
  
  if (root->dragging && root->mouseDownElement != this) {
    if (!prevPos.within(bounds) && relParent.within(bounds)) {
      root->dragEntered.push_back(this);
      auto dragEnter = std::make_shared<Events::DragEnter>();
      dragEnter->pos = relParent;
      dragEnter->start = absToRelParent(root->mouseDownPos);
      dragEnter->delta = dragEnter->pos - dragEnter->start;
      dragEnter->which = root->mouseDownButton;
      pushEvent(dragEnter);
    }
    return true;
  } else if (relParent.within(bounds)) {
    if (!prevPos.within(bounds)) {
      root->mouseEntered.push_back(this);
      auto mouseEnter = std::make_shared<Events::MouseEnter>();
      mouseEnter->pos = absToRel(event->pos);
      pushEvent(mouseEnter);
    }
  
    auto mouseMoveEvent = std::make_shared<Events::MouseMove>();
    mouseMoveEvent->pos = absToRel(event->pos);
    mouseMoveEvent->delta = event->delta;
    pushEvent(mouseMoveEvent);
    
    return true;
  } else {
    return false;
  }
}

bool Element::handleScroll(std::shared_ptr<Input::Scroll> event) {
  if (absToRelParent(event->pos).within(bounds)) {
    if (canHandleScroll(event->delta)) {
      auto scroll = std::make_shared<Events::Scroll>();
      scroll->pos = absToRel(event->pos);
      scroll->delta = event->delta;
      pushEvent(scroll);
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

void Element::handleKeyDown(std::shared_ptr<Input::KeyDown> event) {
  if (!event->repeat) {
    auto keyDown = std::make_shared<Events::KeyDown>();
    keyDown->key = event->key;
    keyDown->modifiers = event->modifiers;
    pushEvent(keyDown);
  }
  
  auto keyPress = std::make_shared<Events::KeyPress>();
  keyPress->key = event->key;
  keyPress->character = event->character;
  pushEvent(keyPress);
}

void Element::handleKeyUp(std::shared_ptr<Input::KeyUp> event) {
  auto keyUp = std::make_shared<Events::KeyUp>();
  keyUp->key = event->key;
  pushEvent(keyUp);
}

Geometry::Point Element::absToRel(Geometry::Point abs) {
  Element *parentElement = dynamic_cast<Element *>(parent);
  if (parentElement) {
    return parentElement->absToRel(abs - bounds.p);
  } else {
    return abs;
  }
}

Geometry::Point Element::absToRelParent(Geometry::Point abs) {
  return absToRel(abs) + bounds.p;
}

Geometry::Point Element::relToAbs(Geometry::Point rel) {
  Element *parentElement = dynamic_cast<Element *>(parent);
  if (parentElement) {
    return parentElement->relToAbs(rel + bounds.p);
  } else {
    return rel;
  }
}

Geometry::Point Element::relParentToAbs(Geometry::Point relParent) {
  return relToAbs(relParent - bounds.p);
}

Geometry::Point Element::relToRelParent(Geometry::Point rel) {
  return rel + bounds.p;
}

Geometry::Point Element::relParentToRel(Geometry::Point relParent) {
  return relParent - bounds.p;
}
