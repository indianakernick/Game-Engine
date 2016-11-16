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
  inline uint64_t getNanoI() {
    return std::chrono::high_resolution_clock::now().time_since_epoch().count();
  }
  inline uint64_t getMicroI() {
    return getNanoI() * Math::SI::NANO_MICRO;
  }
  inline uint64_t getMilliI() {
    return getNanoI() * Math::SI::NANO_MILLI;
  }
  inline uint64_t getSecI() {
    return getNanoI() * Math::SI::NANO_ONE;
  }
  
  inline double getNanoF() {
    return std::chrono::high_resolution_clock::now().time_since_epoch().count();
  }
  inline uint64_t getMicroF() {
    return getNanoF() * Math::SI::NANO_MICRO;
  }
  inline double getMilliF() {
    return getNanoF() * Math::SI::NANO_MILLI;
  }
  inline double getSecF() {
    return getNanoF() * Math::SI::NANO_ONE;
  }
  
  //Get the unix timestamp
  inline uint64_t getDate() {
    return std::chrono::system_clock::now().time_since_epoch().count() * Math::SI::MICRO_ONE;
  }
};

#endif
