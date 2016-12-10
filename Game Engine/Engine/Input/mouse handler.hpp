//
//  mouse handler.hpp
//  Game Engine
//
//  Created by Indi Kernick on 4/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_input_mouse_handler_hpp
#define engine_input_mouse_handler_hpp

#include "../Geometry/point.hpp"
#include <memory>
#include "mouse.hpp"

namespace Input {
  class Manager;

  class MouseHandler {
  friend class Manager;
  public:
    using Ptr = std::shared_ptr<MouseHandler>;
  
    MouseHandler() = default;
    virtual ~MouseHandler() = default;
    
    //returning true means that the event was handled and no other handlers
    //need to see it
    virtual bool onMove(Geometry::Point pos, Geometry::Point delta) = 0;
    virtual bool onDown(Geometry::Point pos, MButton::Type which) = 0;
    virtual bool onUp(Geometry::Point pos, MButton::Type which) = 0;
    virtual bool onScroll(Geometry::Point pos, Geometry::Point scrollDelta) = 0;
  
  protected:
    void captureOn();
    void captureOff();
  private:
    Manager *manager = nullptr;
  };
}

#include "manager.hpp"

#endif
