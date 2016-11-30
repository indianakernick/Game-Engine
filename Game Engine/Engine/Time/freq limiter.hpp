//
//  freq limiter.hpp
//  Game Engine
//
//  Created by Indi Kernick on 21/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_time_freq_limiter_hpp
#define engine_time_freq_limiter_hpp

#include "get.hpp"

namespace Time {
  ///Limits the frequency of some operation
  template <typename DURATION_TYPE>
  class FreqLimiter {
  public:
    explicit FreqLimiter(uint64_t count)
      : duration(count),
        lastDo(getPoint<DURATION_TYPE>() - duration) {}
    
    ///If this function returns true, it will not return true again until the
    ///duration has passed
    bool canDo() {
      Point<DURATION_TYPE> now = getPoint<DURATION_TYPE>();
      if (now - lastDo >= duration) {
        lastDo = now;
        return true;
      } else {
        return false;
      }
    }
    
  private:
    //minumum duration between operations
    const DURATION_TYPE duration;
    //time of last operation
    Point<DURATION_TYPE> lastDo;
  };
}

#endif
