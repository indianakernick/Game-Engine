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
#include <functional>
#include "../../ID/global.hpp"
#include "../../Utils/safe down cast.hpp"

namespace UI {
  class Event {
  public:
    using Type = uint32_t;
    using Ptr = std::shared_ptr<Event>;
  
    Event() = default;
    virtual ~Event() = default;
  
    virtual Type getType() const = 0;
    virtual const char *getName() const = 0;
  };
  
  using EventTypeGen = ID::Global<Event::Type, Event>;
  
  class MouseDown final : public Event {
  public:
    using Ptr = std::shared_ptr<MouseDown>;
    static const Type TYPE;
    
    Type getType() const override;
    const char *getName() const override;
  };
  
  class MouseUp final : public Event {
  public:
    using Ptr = std::shared_ptr<MouseUp>;
    static const Type TYPE;
    
    explicit MouseUp(bool);
    
    bool within;
    
    Type getType() const override;
    const char *getName() const override;
  };
  
  class MouseEnter final : public Event {
  public:
    using Ptr = std::shared_ptr<MouseEnter>;
    static const Type TYPE;
    
    explicit MouseEnter(bool);
    
    bool down;
    
    Type getType() const override;
    const char *getName() const override;
  };
  
  class MouseLeave final : public Event {
  public:
    using Ptr = std::shared_ptr<MouseLeave>;
    static const Type TYPE;
    
    explicit MouseLeave(bool);
    
    bool down;
    
    Type getType() const override;
    const char *getName() const override;
  };
  
  class MouseMove final : public Event {
  public:
    using Ptr = std::shared_ptr<MouseMove>;
    static const Type TYPE;
    
    Point relPos;       //the mouse pos in relative space
    Point relParPos;    //the mouse pos relative to parent
    Point absPos;       //the mouse pos in absolute space
    Point relDelta;     //the mouse delta in relative space
    Point relParDelta;  //the mouse delta relative to parent
    Point absDelta;     //the mouse delta in absolute space
    bool down;          //the mouse is down
    
    Type getType() const override;
    const char *getName() const override;
  };
}

#endif
