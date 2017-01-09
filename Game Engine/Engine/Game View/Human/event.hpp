//
//  event.hpp
//  Game Engine
//
//  Created by Indi Kernick on 11/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_game_view_human_event_hpp
#define engine_game_view_human_event_hpp

#include <cstdint>
#include "../../Geometry/point.hpp"
#include "../../Input/State/mouse.hpp"
#include "../../Input/State/keyboard.hpp"
#include "../../Geometry/size.hpp"
#include <memory>

class Element;

namespace Events {
  enum Type : uint8_t {
    MOUSE_DOWN,
    MOUSE_UP,
    CLICK,
    //double click
    DBL_CLICK,
    
    MOUSE_MOVE,
    SCROLL,
    
    //the mouse was previously not within the bounds of the element but now
    //it is
    MOUSE_ENTER,
    MOUSE_LEAVE,
    
    //the mouse moved while the button was down
    DRAG_START,
    //the mouse has moved since DRAG_START
    DRAG,    
    //drag enter and leave events are sent to the dragged element and
    //the element being entered and left
    
    //the mouse has entered this element while a drag is in progress
    DRAG_ENTER,
    //the mouse has left this element while a drag is in progress
    //this may include the element which the drag started on
    DRAG_LEAVE,
    //the button has been released
    DRAG_END,
    
    //the element previously didn't have focus but now it does
    FOCUS_GAINED,
    FOCUS_LOST,
    
    //the key has been pressed
    KEY_DOWN,
    //the key has been released
    KEY_UP,
    //the key has either been pressed or is repeating
    //use this for text boxs
    KEY_PRESS,
    
    //the window this element is in has changed size
    WINDOW_RESIZE
  };
  
  class Event {
  public:
    using Ptr = std::shared_ptr<Event>;
  
    virtual ~Event() = default;
  
    virtual Type getType() const = 0;
  };
  
  class MouseDown : public Event {
  public:
    static const Type TYPE;
    
    Geometry::Point pos;
    Input::MButton::Type which;
    
    Type getType() const override;
  };
  
  class MouseUp : public Event {
  public:
    static const Type TYPE;
    
    Geometry::Point pos;
    Input::MButton::Type which;
    
    Type getType() const override;
  };
  
  class Click : public Event {
  public:
    static const Type TYPE;
    
    Geometry::Point pos;
    Input::MButton::Type which;
    
    Type getType() const override;
  };
  class DblClick : public Event {
  public:
    static const Type TYPE;
    
    Geometry::Point pos;
    Input::MButton::Type which;
    
    Type getType() const override;
  };
  
  class MouseMove : public Event {
  public:
    static const Type TYPE;
    
    Geometry::Point pos;
    Geometry::Point delta;
    
    Type getType() const override;
  };
  
  class Scroll : public Event {
  public:
    static const Type TYPE;
    
    Geometry::Point pos;
    Geometry::Point delta;
    
    Type getType() const override;
  };
  
  class MouseEnter : public Event {
  public:
    static const Type TYPE;
    
    Geometry::Point pos;
    
    Type getType() const override;
  };
  
  class MouseLeave : public Event {
  public:
    static const Type TYPE;
    
    Geometry::Point pos;
    
    Type getType() const override;
  };
  
  class DragStart : public Event {
  public:
    static const Events::Type TYPE;
    
    ///Position of mouse relative to parent
    Geometry::Point pos;
    Input::MButton::Type which;
    
    Type getType() const override;
  };
  
  class Drag : public Event {
  public:
    static const Events::Type TYPE;
    
    ///Position of mouse relative to parent
    Geometry::Point pos;
    ///Starting position relative to parent
    Geometry::Point start;
    ///Distance from starting position
    Geometry::Point delta;
    Input::MButton::Type which;
    
    Type getType() const override;
  };
  
  class DragEnter : public Event {
  public:
    static const Events::Type TYPE;
    
    ///Position or mouse relative to parent
    Geometry::Point pos;
    ///Starting position relative to parent
    Geometry::Point start;
    ///Distance from starting position
    Geometry::Point delta;
    Input::MButton::Type which;
    
    //the element that is being dragged
    Element *dragged;
    //the element that the dragged element is entering
    Element *entering;
    
    Type getType() const override;
  };
  
  class DragLeave : public Event {
  public:
    static const Events::Type TYPE;
    
    ///Position or mouse relative to parent
    Geometry::Point pos;
    ///Starting position relative to parent
    Geometry::Point start;
    ///Distance from starting position
    Geometry::Point delta;
    Input::MButton::Type which;
    
    Type getType() const override;
  };
  
  class DragEnd : public Event {
  public:
    static const Events::Type TYPE;
    
    ///Position or mouse relative to parent
    Geometry::Point pos;
    ///Starting position relative to parent
    Geometry::Point start;
    ///Distance from starting position
    Geometry::Point delta;
    Input::MButton::Type which;
    //the element the dragged object was dropped onto
    Element *dropped;
    //the dragged object
    Element *dragged;
    
    Type getType() const override;
  };
  
  class FocusGained : public Event {
  public:
    static const Events::Type TYPE;
    
    ///The element that had focus before this one did
    Element *prev;
    
    Type getType() const override;
  };
  
  class FocusLost : public Event {
  public:
    static const Events::Type TYPE;
  
    ///The element that currently has focus
    Element *now;
    
    Type getType() const override;
  };
  
  class KeyDown : public Event {
  public:
    static const Events::Type TYPE;
  
    Input::Key::Type key;
    Input::Mod::Type modifiers;
    
    Type getType() const override;
  };
  
  class KeyUp : public Event {
  public:
    static const Events::Type TYPE;
    
    Input::Key::Type key;
    
    Type getType() const override;
  };
  
  class KeyPress : public Event {
  public:
    static const Events::Type TYPE;
    
    Input::Key::Type key;
    char character;
    
    Type getType() const override;
  };
  
  class WindowResize : public Event {
  public:
    static const Events::Type TYPE;
    
    Geometry::Size size;
    Geometry::Size prevSize;
    
    Type getType() const override;
  };
}

#endif
