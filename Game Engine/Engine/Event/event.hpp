//
//  event.hpp
//  Game Engine
//
//  Created by Indi Kernick on 11/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_event_event_hpp
#define engine_event_event_hpp

#include <cstdint>
#include <memory>

namespace Game {
  class Event {
  public:
    using Type = uint32_t;
    using Ptr = std::shared_ptr<Event>;
    
    Event() = default;
    virtual ~Event() = default;
    
    virtual Type getType() const = 0;
    virtual const char *getName() const = 0;
  };
}

#endif
