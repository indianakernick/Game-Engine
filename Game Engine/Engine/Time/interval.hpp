//
//  interval.hpp
//  Game Engine
//
//  Created by Indi Kernick on 26/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef interval_hpp
#define interval_hpp

#include "get.hpp"
#include <thread>
#include <functional>

namespace Time {
  ///Block the thread to align the execution of a loop to a set interval
  template <typename DURATION_TYPE>
  class IntervalSync {
  public:
    IntervalSync(uint64_t count)
      : duration(count), lastTime(getPoint<DURATION_TYPE>()) {}
    
    ///Realigns the interval with the current time
    void reset() {
      lastTime = getPoint<DURATION_TYPE>();
    }
    
    ///Chanages the duration of the interval
    void reset(DURATION_TYPE newDuration) {
      duration = newDuration;
      lastTime = getPoint<DURATION_TYPE>();
    }
    
    ///Waits until the end of the interval
    void wait() {
      DURATION_TYPE runTime = getPoint<DURATION_TYPE>() - lastTime;
      lastTime += duration * (runTime / duration + 1);
      std::this_thread::sleep_until(lastTime);
    }
  private:
    DURATION_TYPE duration;
    //the last time wait returned
    Point<DURATION_TYPE> lastTime;
  };
  
  ///Calls a function ptr from another thread at an interval
  template <typename DURATION_TYPE>
  class IntervalAsync {
  public:
    IntervalAsync(uint64_t count, std::function<void ()> func)
      : running(false), thread(threadFunc, &running, count, func) {}
    
    ~IntervalAsync() {
      thread.detach();
    }
    
    void start() {
      running = true;
    }
    void stop() {
      running = false;
    }
  private:
    std::atomic<bool> running;
    std::thread thread;
    
    static void threadFunc(std::atomic<bool> *running,
                           uint64_t count,
                           std::function<void ()> func) {
      IntervalSync<DURATION_TYPE> interval(count);
      bool wasRunning = false;
      while (true) {
        if (*running) {
          if (!wasRunning) {
            interval.reset();
          }
          func();
          wasRunning = true;
        } else {
          wasRunning = false;
        }
        interval.wait();
      }
    }
  };
}

#endif
