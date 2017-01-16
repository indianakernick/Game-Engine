//
//  event listener.hpp
//  Game Engine
//
//  Created by Indi Kernick on 15/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_input_event_listener_hpp
#define engine_input_event_listener_hpp

#include "event.hpp"

namespace Input {
  enum : bool {
    NOT_HANDLED = false,
    HANDLED = true,
  };

  class EventListener {
  public:
    using Ptr = std::shared_ptr<EventListener>;
  
    EventListener() = default;
    virtual ~EventListener() = default;
    
    virtual bool onMouseDown(const MouseDown *);
    virtual bool onMouseUp(const MouseUp *);
    virtual bool onMouseMove(const MouseMove *);
    virtual bool onScroll(const Scroll *);
    virtual bool onKeyDown(const KeyDown *);
    virtual bool onKeyUp(const KeyUp *);
    virtual bool onWindowResize(const WindowResize *);
    virtual bool onQuit(const Quit *);
  };
}

#endif
