//
//  range.hpp
//  Game Engine
//
//  Created by Indi Kernick on 4/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef range_hpp
#define range_hpp

#include <cassert>

namespace Math {
  template <typename T>
  class Range {
  public:
    Range(T min, T max)
      : min(min), max(max) {
      assert(min < max);
    }
    
    bool within(T num) const {
      return min <= num && num <= max;
    }
    
    bool overlap(const Range<T> &other) const {
      return min < other.max && other.min < max;
    }
    
    ///first argument is within the second argument
    static bool within(const Range<T> &a, const Range<T> &b) {
      return b.min <= a.min && a.max <= b.max;
    }
    
    T min;
    T max;
  };
};

#endif
