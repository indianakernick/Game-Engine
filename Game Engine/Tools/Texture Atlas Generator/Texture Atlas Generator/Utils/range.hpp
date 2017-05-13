//
//  range.hpp
//  Texture Atlas Generator
//
//  Created by Indi Kernick on 13/5/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef utils_range_hpp
#define utils_range_hpp

#include <vector>
#include <cassert>
#include <iterator>

///A contigious range
template <typename T>
class RangeView {
public:
  using reference = const T &;
  using const_reference = const T &;
  using iterator = const T *;
  using const_iterator = const T *;
  using value_type = const T;
  using pointer = const T *;
  using const_pointer = const T *;

  RangeView() = default;
  RangeView(const T *begin, const T *end)
    : mBegin(begin), mEnd(end) {
    assert(begin <= end);
  }

  void begin(const T *newBegin) {
    mBegin = newBegin;
    assert(mBegin <= mEnd);
  }
  const T *begin() const {
    return mBegin;
  }
  const T *cbegin() const {
    return mBegin;
  }
  
  void end(const T *newEnd) {
    mEnd = newEnd;
    assert(mBegin <= mEnd);
  }
  const T *end() const {
    return mEnd;
  }
  const T *cend() const {
    return mEnd;
  }
  
  const T &front() const {
    assert(size());
    return *mBegin;
  }
  
  const T &back() const {
    assert(size());
    return *(mEnd - 1);
  }
  
  void size(size_t newSize) {
    mEnd = mBegin + newSize;
  }
  size_t size() const {
    return mEnd - mBegin;
  }
  
  const T &operator[](const size_t i) const {
    assert(i < size());
    return mBegin[i];
  }
private:
  const T *mBegin;
  const T *mEnd;
};

template <typename T>
RangeView<T> makeRangeView(const std::vector<T> &container) {
  return {container.data(), container.data() + container.size()};
}

#endif
