//
//  events.hpp
//  Game Engine
//
//  Created by Indi Kernick on 3/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_game_view_human_events_hpp
#define engine_game_view_human_events_hpp

#include <memory>
#include "types.hpp"
#include "../../ID/type.hpp"

namespace UI {
  class Event {
  public:
    using Type = uint32_t;
    using Ptr = std::shared_ptr<Event>;
  
    Event() = default;
    virtual ~Event() = default;
  };
  
  template <typename EventClass>
  using GetEventType = ID::TypeCounter<Event::Type, EventClass, Event>;
  
  class MouseDown final : public Event {
  public:
    using Ptr = std::shared_ptr<MouseDown>;
  };
  
  class MouseUp final : public Event {
  public:
    using Ptr = std::shared_ptr<MouseUp>;
    
    explicit MouseUp(bool);
    
    bool within;
  };
  
  class MouseEnter final : public Event {
  public:
    using Ptr = std::shared_ptr<MouseEnter>;
    
    explicit MouseEnter(bool);
    
    bool down;
  };
  
  class MouseLeave final : public Event {
  public:
    using Ptr = std::shared_ptr<MouseLeave>;
    
    explicit MouseLeave(bool);
    
    bool down;
  };
  
  class MouseMove final : public Event {
  public:
    using Ptr = std::shared_ptr<MouseMove>;
    
    Point relPos;       //the mouse pos in relative space
    Point relParPos;    //the mouse pos relative to parent
    Point absPos;       //the mouse pos in absolute space
    Point relDelta;     //the mouse delta in relative space
    Point relParDelta;  //the mouse delta relative to parent
    Point absDelta;     //the mouse delta in absolute space
    bool down;          //the mouse is down
  };
}

#endif
