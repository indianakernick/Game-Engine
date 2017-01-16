//
//  event.cpp
//  Game Engine
//
//  Created by Indi Kernick on 11/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "event.hpp"

#define DEFINE_TYPE(class, enum) const Events::Type Events::class::TYPE = Events::enum;

DEFINE_TYPE(MouseDown, MOUSE_DOWN)
DEFINE_TYPE(MouseUp, MOUSE_UP)
DEFINE_TYPE(Click, CLICK)
DEFINE_TYPE(DblClick, DBL_CLICK)
DEFINE_TYPE(MouseMove, MOUSE_MOVE)
DEFINE_TYPE(Scroll, SCROLL)
DEFINE_TYPE(MouseEnter, MOUSE_ENTER)
DEFINE_TYPE(MouseLeave, MOUSE_LEAVE)

DEFINE_TYPE(DragStart, DRAG_START)
DEFINE_TYPE(Drag, DRAG)
DEFINE_TYPE(DragEnter, DRAG_ENTER)
DEFINE_TYPE(DragLeave, DRAG_LEAVE)
DEFINE_TYPE(DragEnd, DRAG_END)

DEFINE_TYPE(FocusGained, FOCUS_GAINED)
DEFINE_TYPE(FocusLost, FOCUS_LOST)

DEFINE_TYPE(KeyDown, KEY_DOWN)
DEFINE_TYPE(KeyUp, KEY_UP)
DEFINE_TYPE(KeyPress, KEY_PRESS)

DEFINE_TYPE(WindowResize, WINDOW_RESIZE);

#define ACCEPT(class) void Events::class::accept(EventElement *element) const {\
  element->dispatch(*this);\
}

ACCEPT(MouseDown)
ACCEPT(MouseUp)
ACCEPT(Click)
ACCEPT(DblClick)
ACCEPT(MouseMove)
ACCEPT(Scroll)
ACCEPT(MouseEnter)
ACCEPT(MouseLeave)

ACCEPT(DragStart)
ACCEPT(Drag)
ACCEPT(DragEnter)
ACCEPT(DragLeave)
ACCEPT(DragEnd)

ACCEPT(FocusGained)
ACCEPT(FocusLost)

ACCEPT(KeyDown)
ACCEPT(KeyUp)
ACCEPT(KeyPress)

ACCEPT(WindowResize)
