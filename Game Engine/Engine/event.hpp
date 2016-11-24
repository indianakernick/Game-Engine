//
//  event.hpp
//  Game Engine
//
//  Created by Indi Kernick on 11/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef event_hpp
#define event_hpp

#include <cstdint>

class Event {
public:
  using Type = uint64_t;
  
  virtual Type getType() const = 0;
};

#endif
