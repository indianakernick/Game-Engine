//
//  time.hpp
//  Game Engine
//
//  Created by Indi Kernick on 14/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef time_hpp
#define time_hpp

#include <chrono>
#include "Math/siconstants.hpp"

namespace Time {
  ///Get current time in nanoseconds as an integer
  inline uint64_t getNanoI() {
    return std::chrono::high_resolution_clock::now().time_since_epoch().count();
  }
  ///Get current time in microseconds as an integer
  inline uint64_t getMicroI() {
    return getNanoI() * Math::SI::NANO_MICRO;
  }
  ///Get current time in milliseconds as an integer
  inline uint64_t getMilliI() {
    return getNanoI() * Math::SI::NANO_MILLI;
  }
  ///Get current time in seconds as an integer
  inline uint64_t getSecI() {
    return getNanoI() * Math::SI::NANO_ONE;
  }
  
  ///Get current time in nanoseconds as floating point number
  inline double getNanoF() {
    return std::chrono::high_resolution_clock::now().time_since_epoch().count();
  }
  ///Get current time in microseconds as floating point number
  inline double getMicroF() {
    return getNanoF() * Math::SI::NANO_MICRO;
  }
  ///Get current time in milliseconds as floating point number
  inline double getMilliF() {
    return getNanoF() * Math::SI::NANO_MILLI;
  }
  ///Get current time in seconds as floating point number
  inline double getSecF() {
    return getNanoF() * Math::SI::NANO_ONE;
  }
  
  ///Get the Unix timestamp
  inline uint64_t getDate() {
    return std::chrono::system_clock::now().time_since_epoch().count() * Math::SI::MICRO_ONE;
  }
};

#endif
