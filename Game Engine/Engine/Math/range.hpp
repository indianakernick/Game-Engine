//
//  range.hpp
//  Game Engine
//
//  Created by Indi Kernick on 4/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_math_range_hpp
#define engine_math_range_hpp

#include <cassert>
#include <algorithm>
#include <iostream>

namespace Math {
  template <typename T>
  class Range {
  public:
    Range(const T &min, const T &max)
      : min(min), max(max) {
      assert(isValid());
    }
    Range(const Range<T> &) = default;
    Range(Range<T> &&) = default;
    ~Range() = default;
    
    Range<T> &operator=(const Range<T> &) = default;
    Range<T> &operator=(Range<T> &&) = default;
    
    bool operator==(const Range<T> &other) {
      return min == other.min && max == other.max;
    }
    bool operator!=(const Range<T> &other) {
      return min != other.min || max != other.max;
    }
    
    friend std::ostream &operator<<(std::ostream &stream, const Range<T> &range) {
      return stream << std::move(range);
    }
    friend std::ostream &operator<<(std::ostream &stream, const Range<T> &&range) {
      return stream << '[' << range.min << ", " << range.max << ']';
    }
    
    bool within(const T &num) const {
      return min <= num && num <= max;
    }
    
    bool within(const Range<T> &other) {
      return other.min <= min && max <= other.max;
    }
    
    bool overlap(const Range<T> &other) const {
      return min < other.max && other.min < max;
    }
    
    //if the returned range is invalid then the two ranges don't overlap
    Range<T> overlapRange(const Range<T> &other) const {
      if (max < other.max) {
        return {other.min, max};
      } else {
        return {min, other.max};
      }
    }
    
    T width() const {
      return max - min + 1;
    }
    
    T center() const {
      return min + width() / 2;
    }
    
    bool isValid() const {
      return min <= max;
    }
    
    void norm() {
      if (!isValid()) {
        std::swap(min, max);
      }
    }
    
    T min;
    T max;
  };
};

#endif
