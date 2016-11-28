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
#include <memory>
#include <string>
#include "../Time/get.hpp"

class Event {
public:
  using Type = uint64_t;
  using Ptr = std::shared_ptr<Event>;
  
  Event();
  
  virtual Type getType() const = 0;
  virtual std::string getName() const = 0;
  
  uint64_t getTime();
  void setTime();
private:
  //milliseconds
  uint64_t time;
};

#endif
