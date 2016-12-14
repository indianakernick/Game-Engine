//
//  event.hpp
//  Game Engine
//
//  Created by Indi Kernick on 11/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_input_event_hpp
#define engine_input_event_hpp

#include <memory>
#include "../Geometry/point.hpp"
#include "State/mouse.hpp"
#include "State/keyboard.hpp"

namespace Input {
  enum Type : uint8_t {
    MOUSE_DOWN,
    MOUSE_UP,
    MOUSE_MOVE,
    SCROLL,
    KEY_DOWN,
    KEY_UP,
    WINDOW_RESIZE
  };
  
  class Event {
  public:
    using Ptr = std::shared_ptr<Event>;
    
    virtual Type getType() const = 0;
  };
  
  class MouseDown : public Event {
  public:
    static const Type TYPE;
  
    Geometry::Point pos;
    MButton::Type button;
    int repeat;
    
    Type getType() const override;
  };
  
  class MouseUp : public Event {
  public:
    static const Type TYPE;

    Geometry::Point pos;
    MButton::Type button;
    
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
  
  class KeyDown : public Event {
  public:
    static const Type TYPE;

    Key::Type key;
    Mod::Type modifiers;
    char character;
    int repeat;
    
    Type getType() const override;
  };
  
  class KeyUp : public Event {
  public:
    static const Type TYPE;

    Key::Type key;
    
    Type getType() const override;
  };
  
  class WindowResize : public Event {
  public:
    static const Type TYPE;

    Geometry::Size size;
    Geometry::Size prevSize;
    
    Type getType() const override;
  };
}

#endif
