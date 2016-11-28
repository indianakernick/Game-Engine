//
//  timer.hpp
//  Game Engine
//
//  Created by Indi Kernick on 28/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef timer_hpp
#define timer_hpp

#include "get.hpp"
#include <cassert>

namespace Time {
  template <typename DURATION_TYPE>
  class Timer {
  public:
    Timer() = default;
    
    ///Starts the timer
    void start() {
      assert(!running);
      running = true;
      startTime = getPoint<DURATION_TYPE>();
    }
    ///Stops the timer and returns the duration
    uint64_t stop() {
      assert(running);
      endTime = getPoint<DURATION_TYPE>();
      running = false;
      return (endTime - startTime).count();
    }
    ///Resume the timer after it has been stopped, returning the duration
    uint64_t resume() {
      assert(!running);
      running = true;
      return (endTime - startTime).count();
    }
    ///Gets the duration. Can be called while the timer is running
    uint64_t get() {
      return (endTime - startTime).count();
    }
    ///Returns the duration and resets the timer
    uint64_t lap() {
      assert(running);
      uint64_t duration = (endTime - startTime).count();
      startTime = getPoint<DURATION_TYPE>();
      return duration;
    }
    ///Returns whether the timer is running (start has just been called).
    bool isRunning() {
      return running;
    }
  private:
    Point<DURATION_TYPE> startTime = 0;
    Point<DURATION_TYPE> endTime = 0;
    bool running = false;
  };
}

#endif
