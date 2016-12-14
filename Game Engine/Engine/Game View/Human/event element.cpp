//
//  event element.cpp
//  Game Engine
//
//  Created by Indi Kernick on 13/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "event element.hpp"

void EventElement::pushEvent(Events::Event::Ptr event) {
  eventQueue.push(event);
}

void EventElement::dispatchEvents() {
  while (!eventQueue.empty()) {
    Events::Event::Ptr &event = eventQueue.front();
    dispatchEvent(event);
    eventQueue.pop();
  }
}

#define DISPATCH(name) dispatch(*std::dynamic_pointer_cast<name>(event))

void EventElement::dispatchEvent(Events::Event::Ptr event) {
  using namespace Events;
  
  switch (event->getType()) {
    case MOUSE_DOWN:
      DISPATCH(MouseDown);
      break;
    case MOUSE_UP:
      DISPATCH(MouseUp);
      break;
    case CLICK:
      DISPATCH(Click);
      break;
    case DBL_CLICK:
      DISPATCH(DblClick);
      break;
    case MOUSE_MOVE:
      DISPATCH(MouseMove);
      break;
    case SCROLL:
      DISPATCH(Scroll);
      break;
    case MOUSE_ENTER:
      DISPATCH(MouseEnter);
      break;
    case MOUSE_LEAVE:
      DISPATCH(MouseLeave);
      break;
      
    case DRAG_START:
      DISPATCH(DragStart);
      break;
    case DRAG:
      DISPATCH(Drag);
      break;
    case DRAG_ENTER:
      DISPATCH(DragEnter);
      break;
    case DRAG_LEAVE:
      DISPATCH(DragLeave);
      break;
    case DRAG_END:
      DISPATCH(DragEnd);
      break;
    
    case FOCUS_GAINED:
      DISPATCH(FocusGained);
      break;
    case FOCUS_LOST:
      DISPATCH(FocusLost);
      break;
    
    case KEY_DOWN:
      DISPATCH(KeyDown);
      break;
    case KEY_UP:
      DISPATCH(KeyUp);
      break;
    case KEY_PRESS:
      DISPATCH(KeyPress);
      break;
    
    case WINDOW_RESIZE:
      DISPATCH(WindowResize);
      break;
  }
}
