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
#include <string>

class Event {
public:
  using Type = uint64_t;
  using Ptr = std::shared_ptr<Event>;
  
  Event() = default;
  virtual ~Event() = default;
  
  virtual Type getType() const = 0;
  virtual std::string getName() const = 0;
};

#endif
