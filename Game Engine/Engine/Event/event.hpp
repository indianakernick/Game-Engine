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
#include <cassert>

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
  
  template <typename T>
  inline std::enable_if_t<std::is_base_of<Event, T>::value, std::shared_ptr<T>>
  castEvent(const Event::Ptr event) {
    const std::shared_ptr<T> newEvent = std::dynamic_pointer_cast<T>(event);
    assert(newEvent);
    return newEvent;
  }
}

#endif
