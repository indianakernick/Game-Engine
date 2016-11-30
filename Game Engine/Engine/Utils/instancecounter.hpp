//
//  instancecounter.hpp
//  Game Engine
//
//  Created by Indi Kernick on 8/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_instancecounter_hpp
#define engine_utils_instancecounter_hpp

#include <cstddef>
#include <cassert>

template <typename T, size_t MAX_COUNT>
class InstanceCounter {
private:
  InstanceCounter() {
    count++;
    assert(count <= MAX_COUNT);
  }
  InstanceCounter(const InstanceCounter &) {
    count++;
    assert(count <= MAX_COUNT);
  }
  InstanceCounter(InstanceCounter &&) {
    count++;
    //no need to check because an object is about to be destroyed
  }
  ~InstanceCounter() {
    count--;
  }
  
  InstanceCounter &operator=(const InstanceCounter &) = default;
  InstanceCounter &operator=(InstanceCounter &&) = default;
  
  static size_t count;
};

#endif
