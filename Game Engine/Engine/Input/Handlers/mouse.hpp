//
//  mouse.hpp
//  Game Engine
//
//  Created by Indi Kernick on 4/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_input_handlers_mouse_hpp
#define engine_input_handlers_mouse_hpp

#include "../../Geometry/point.hpp"
#include <memory>
#include "../State/mouse.hpp"

namespace Input {
  class Manager;
  namespace Handlers {
    class Mouse {
    friend class ::Input::Manager;
    public:
      using Ptr = std::shared_ptr<Mouse>;
    
      Mouse() = default;
      virtual ~Mouse() = default;
      
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
}

#include "../manager.hpp"

#endif
