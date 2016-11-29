//
//  get.hpp
//  Game Engine
//
//  Created by Indi Kernick on 14/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef get_hpp
#define get_hpp

#include <chrono>
#include <ctime>
#include "../Math/siconstants.hpp"

namespace Time {
  ///Get the current time as an integer
  template <typename DURATION_TYPE>
  inline uint64_t getI() {
    return std::chrono::duration_cast<DURATION_TYPE>(
      std::chrono::high_resolution_clock::now()
      .time_since_epoch()
    )
    .count();
  }
  
  template <typename DURATION_TYPE>
  using Point = std::chrono::time_point<std::chrono::high_resolution_clock, DURATION_TYPE>;
  
  ///Get the current time as a std::chrono::time_point
  template <typename DURATION_TYPE>
  inline Point<DURATION_TYPE> getPoint() {
    return std::chrono::time_point_cast<DURATION_TYPE>(
      std::chrono::high_resolution_clock::now()
    );
  }
  
  ///Get the current time as a std::chrono::duration since epoch
  template <typename DURATION_TYPE>
  inline DURATION_TYPE getDuration() {
    return std::chrono::duration_cast<DURATION_TYPE>(
      std::chrono::high_resolution_clock::now()
      .time_since_epoch()
    );
  }
  
  ///Get the current time as a floating-point number
  template <typename DURATION_TYPE>
  inline double getF();
  
  template <>
  inline double getF<std::chrono::nanoseconds>() {
    return getI<std::chrono::nanoseconds>();
  }
  
  template <>
  inline double getF<std::chrono::microseconds>() {
    return getI<std::chrono::nanoseconds>() * Math::SI::NANO_MICRO;
  }
  
  template <>
  inline double getF<std::chrono::milliseconds>() {
    return getI<std::chrono::nanoseconds>() * Math::SI::NANO_MILLI;
  }
  
  template <>
  inline double getF<std::chrono::seconds>() {
    return getI<std::chrono::nanoseconds>() * Math::SI::NANO_ONE;
  }
  
  ///Get the Unix timestamp
  inline uint64_t getDate() {
    return std::chrono::duration_cast<std::chrono::seconds>(
      std::chrono::system_clock::now()
      .time_since_epoch()
    )
    .count();
  }
  
  ///Get the formatted date as Www Mmm dd hh:mm:ss yyyy
  inline std::string getDateStr() {
    time_t now = time(nullptr);
    return ctime(&now);
  }
  
  ///Get the formatted time as hh:mm:ss
  std::string getTimeStr() {
    std::string out(8, ' ');
    time_t now;
    time(&now);
    tm *timeinfo = localtime(&now);
    strftime(const_cast<char *>(out.c_str()), 9, "%T", timeinfo);
    return out;
  }
};

#endif
