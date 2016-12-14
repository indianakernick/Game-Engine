//
//  root element.cpp
//  Game Engine
//
//  Created by Indi Kernick on 13/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "root element.hpp"

const int RootElement::DRAG_THRESHOLD = 5;

void RootElement::init() {
  for (auto i = children.begin(); i != children.end(); ++i) {
    (*i)->init();
  }
}

void RootElement::input() {
  for (auto i = children.begin(); i != children.end(); ++i) {
    (*i)->input();
  }
}

void RootElement::update(uint64_t delta) {
  for (auto i = children.begin(); i != children.end(); ++i) {
    (*i)->update(delta);
  }
  
  checkOrderChange();
}

void RootElement::render() {
  Geometry::Point zero;
  
  for (auto i = children.begin(); i != children.end(); ++i) {
    (*i)->render(zero);
  }
}

void RootElement::quit() {
  //quit in reverse order to init
  for (auto i = children.rbegin(); i != children.rend(); ++i) {
    (*i)->quit();
  }
}

Element *RootElement::getFocused() {
  return elementWithFocus;
}

bool RootElement::input(Input::Event::Ptr event) {
  switch (event->getType()) {
    case Input::KEY_DOWN:
      if (elementWithFocus) {
        elementWithFocus->handleKeyDown(std::dynamic_pointer_cast<Input::KeyDown>(event));
        return true;
      } else {
        return false;
      }
    case Input::KEY_UP:
      if (elementWithFocus) {
        elementWithFocus->handleKeyUp(std::dynamic_pointer_cast<Input::KeyUp>(event));
        return true;
      } else {
        return false;
      }
    case Input::WINDOW_RESIZE: {
      auto windowResize = std::dynamic_pointer_cast<Input::WindowResize>(event);
      propResize(windowResize);
      return false;
    }
    case Input::MOUSE_UP: {
      auto mouseUp = std::dynamic_pointer_cast<Input::MouseUp>(event);
      handleMouseUp(mouseUp);
      return propMouse(event);
    }
    case Input::MOUSE_MOVE: {
      auto mouseMove = std::dynamic_pointer_cast<Input::MouseMove>(event);
      handleMouseMove(mouseMove);
      return propMouse(event);
    }
    default:
      return propMouse(event);
  }
}

bool RootElement::propMouse(Input::Event::Ptr event) {
  for (auto i = children.rbegin(); i != children.rend(); ++i) {
    if ((*i)->propMouse(event)) {
      return true;
    }
  }
  return false;
}

void RootElement::propResize(std::shared_ptr<Input::WindowResize> event) {
  auto windowResize = std::make_shared<Events::WindowResize>();
  windowResize->prevSize = event->prevSize;
  windowResize->size = event->size;
  for (auto i = children.begin(); i != children.end(); ++i) {
    (*i)->propResize(windowResize);
  }
}

void RootElement::handleMouseUp(std::shared_ptr<Input::MouseUp> event) {
  if (dragging) {
    Element *droppedOnto = nullptr;
    
    //starting from the most recently entered
    for (auto i = dragEntered.rbegin(); i != dragEntered.rend(); ++i) {
      if (mouseDownElement->droppable(*i)) {
        droppedOnto = *i;
        break;
      }
    }
    dragEntered.clear();
    
    //droppedOnto will be nullptr if the drag failed
    
    auto dragEnd = std::make_shared<Events::DragEnd>();
    dragEnd->pos = mouseDownElement->absToRelParent(event->pos);
    dragEnd->start = mouseDownElement->absToRelParent(mouseDownPos);
    dragEnd->delta = dragEnd->pos - dragEnd->start;
    dragEnd->which = mouseDownButton;
    dragEnd->dropped = droppedOnto;
    dragEnd->dragged = mouseDownElement;
    mouseDownElement->pushEvent(dragEnd);
    
    if (droppedOnto) {
      auto drop = std::make_shared<Events::DragEnd>();
      drop->pos = droppedOnto->absToRelParent(mouseDownPos);
      drop->start = droppedOnto->absToRelParent(mouseDownPos);
      drop->delta = drop->pos - drop->start;
      drop->which = mouseDownButton;
      drop->dropped = droppedOnto;
      drop->dragged = mouseDownElement;
    }
    
    mouseDownElement = nullptr;
    dragging = false;
  }
}

void RootElement::handleMouseMove(std::shared_ptr<Input::MouseMove> event) {
  if (!dragging && mouseDownElement && mouseDownElement->draggable()) {
    Geometry::Point delta = event->pos - mouseDownPos;
    if (std::abs(delta.x) > DRAG_THRESHOLD || std::abs(delta.y) > DRAG_THRESHOLD) {
      dragging = true;
      auto dragStart = std::make_shared<Events::DragStart>();
      dragStart->pos = mouseDownElement->absToRelParent(event->pos);
      dragStart->which = mouseDownButton;
      mouseDownElement->pushEvent(dragStart);
    }
  }
  
  if (!dragging && !mouseDownElement) {
    for (auto i = mouseEntered.begin(); i != mouseEntered.end(); ++i) {
      Element *element = *i;
      Geometry::Point relParent = element->absToRelParent(event->pos);
      if (!relParent.within(element->bounds)) {
        auto mouseLeave = std::make_shared<Events::MouseLeave>();
        mouseLeave->pos = relParent;
        element->pushEvent(mouseLeave);
        *i = nullptr;
      }
    }
    mouseEntered.remove(nullptr);
  }
  
  if (dragging) {
    auto dragEvent = std::make_shared<Events::Drag>();
    dragEvent->pos = mouseDownElement->absToRelParent(event->pos);
    dragEvent->start = mouseDownElement->absToRelParent(mouseDownPos);
    dragEvent->delta = dragEvent->pos - dragEvent->start;
    dragEvent->which = mouseDownButton;
    mouseDownElement->pushEvent(dragEvent);
    
    for (auto i = dragEntered.begin(); i != dragEntered.end(); ++i) {
      Element *element = *i;
      Geometry::Point relParent = element->absToRelParent(event->pos);
      if (!relParent.within(element->bounds)) {
        auto dragLeave = std::make_shared<Events::DragLeave>();
        dragLeave->pos = relParent;
        dragLeave->start = element->absToRelParent(mouseDownPos);
        dragLeave->delta = dragLeave->pos - dragLeave->start;
        dragLeave->which = mouseDownButton;
        element->pushEvent(dragLeave);
        *i = nullptr;
      }
    }
    dragEntered.remove(nullptr);
  }
}
