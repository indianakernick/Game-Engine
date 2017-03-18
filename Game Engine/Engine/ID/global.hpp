//
//  global.hpp
//  Game Engine
//
//  Created by Indi Kernick on 17/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_id_global_hpp
#define engine_id_global_hpp

#include <limits>
#include <cassert>

namespace ID {
  ///Creates a globally unique ID. GROUP is a type the identifies this global group
  template <typename T, typename GROUP>
  class Global {
  
    static_assert(std::is_arithmetic<T>::value, "T must be an arithmetic type");
  
  public:
    Global() = delete;
    ~Global() = delete;
  
    ///Make an ID. Only returns positive values. (Even if T is signed)
    static T make() {
      #ifndef NDEBUG
      assert(!prevIsMax && "Too many IDs were made. T is not large enough");
      if (static_cast<T>(prev + 1) == std::numeric_limits<T>::max()) {
        prevIsMax = true;
      }
      #endif
      return ++prev;
    }
    
    ///The next ID will be after the specified ID. next ID = spec ID + 1
    static void nextIsAfter(T id) {
      #ifndef NDEBUG
      if (id == std::numeric_limits<T>::max()) {
        prevIsMax = true;
      } else {
        prevIsMax = false;
      }
      #endif
      prev = id;
    }
 
  private:
    static T prev;
    #ifndef NDEBUG
    static bool prevIsMax;
    #endif
  };
  
  template <typename T, typename GROUP>
  T Global<T, GROUP>::prev = -1;
  
  #ifndef NDEBUG
  template <typename T, typename GROUP>
  bool Global<T, GROUP>::prevIsMax = false;
  #endif
}

#endif
