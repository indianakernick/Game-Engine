//
//  event listener.hpp
//  Game Engine
//
//  Created by Indi Kernick on 15/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef event_listener_hpp
#define event_listener_hpp

#include "event.hpp"

namespace Input {
  enum : bool {
    NOT_HANDLED = false,
    HANDLED = true,
  };

  class EventListener {
  public:
    using Ptr = std::shared_ptr<EventListener>;
  
    explicit EventListener(bool cast = true);
    virtual ~EventListener() = default;
    
    bool handleEvent(Event::Ptr);
  protected:
    bool cast = true;
  private:
    virtual bool onEvent(Event::Ptr);
    virtual bool onMouseDown(MouseDown::Ptr);
    virtual bool onMouseUp(MouseUp::Ptr);
    virtual bool onMouseMove(MouseMove::Ptr);
    virtual bool onScroll(Scroll::Ptr);
    virtual bool onKeyDown(KeyDown::Ptr);
    virtual bool onKeyUp(KeyUp::Ptr);
    virtual bool onWindowResize(WindowResize::Ptr);
    virtual bool onQuit(Quit::Ptr);
  };
}

#endif
