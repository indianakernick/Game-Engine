//
//  freq limiter.hpp
//  Game Engine
//
//  Created by Indi Kernick on 21/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef freq_limiter_hpp
#define freq_limiter_hpp

namespace Time {
  ///Uses an arbitrary type and time unit
  template <typename TIME_TYPE>
  class FreqLimiter {
  public:
    explicit FreqLimiter(TIME_TYPE duration)
      : time(duration), duration(duration) {}
    
    ///Call this function to pass the time
    void update(TIME_TYPE delta) {
      time += delta;
    }
    ///If this function returns true, it will not return true again until the
    ///duration has passed
    bool canDo() {
      if (time >= duration) {
        time = 0;
        return true;
      } else {
        return false;
      }
    }
    
  private:
    //time since last operation
    TIME_TYPE time;
    //minumum duration between operation
    TIME_TYPE duration;
  };
}

#endif
