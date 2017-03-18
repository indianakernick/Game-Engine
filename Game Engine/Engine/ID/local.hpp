//
//  local.hpp
//  Game Engine
//
//  Created by Indi Kernick on 17/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_id_local_hpp
#define engine_id_local_hpp

#include <limits>
#include <cassert>

namespace ID {
  ///Creates an ID unique to the instance
  template <typename T>
  class Local {
  
    static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
  
  public:
    Local() = default;
    ~Local() = default;
  
    ///Make an ID. Only returns positive values. (Even if T is signed)
    T make() {
      #ifndef NDEBUG
      assert(!prevIsMax && "Too many IDs were made. T is not large enough");
      if (static_cast<T>(prev + 1) == std::numeric_limits<T>::max()) {
        prevIsMax = true;
      }
      #endif
      return ++prev;
    }
    
    ///The next ID will be after the specified ID. next ID = spec ID + 1
    void nextIsAfter(T id) {
      #ifndef NDEBUG
      if (id == std::numeric_limits<T>::max()) {
        prevIsMax = true;
      } else {
        prevIsMax = false;
      }
      #endif
      prev = id;
    }
    
    void reset() {
      prev = -1;
      #ifndef NDEBUG
      prevIsMax = false;
      #endif
    }
  private:
    T prev = -1;
    #ifndef NDEBUG
    bool prevIsMax = false;
    #endif
  };
};

#endif
