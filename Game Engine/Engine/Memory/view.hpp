//
//  primview.hpp
//  game engine
//
//  Created by Indi Kernick on 26/09/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef primview_hpp
#define primview_hpp

#include "raw.hpp"
#include <utility>

namespace Buffer {
  ///A Primitive type memory view. For types that don't need their
  ///constructors and destructors called
  template <typename T>
  class PrimView {
  public:
    explicit PrimView(Raw &other)
      : buf(other) {
      assert(other.size() % sizeof(T) == 0);
    }
    explicit PrimView(const size_t size)
      : buf(size * sizeof(T)) {}
    PrimView(const size_t size, const T chunk)
      : buf(size * sizeof(T)) {
      fill(chunk);
    }
    PrimView(const PrimView<T> &) = default;
    PrimView(PrimView<T> &&) = default;
    ~PrimView() = default;
    
    PrimView<T> &operator=(const PrimView<T> &) = default;
    PrimView<T> &operator=(PrimView<T> &&) = default;
    
    bool operator==(const PrimView<T> &other) const {
      return buf == other.buf;
    }
    bool operator!=(const PrimView<T> &other) const {
      return buf != other.buf;
    }
    
    void fill(const T chunk, size_t start = 0, size_t dist = 0) {
      buf.fill(&chunk, sizeof(T), start * sizeof(T), dist * sizeof(T));
    }
    
    size_t find(const T chunk, size_t start = 0, size_t dist = 0) const {
      if (sizeof(T) == 1) {
        return buf.find(reinterpret_cast<Byte>(chunk), start, dist);
      } else {
        size_t result = buf.find(&chunk,
                                 sizeof(T),
                                 start * sizeof(T),
                                 dist * sizeof(T));
        //we have to make sure that the result is aligned because memmem
        //finds ANY substring in the string not just the substrings that
        //are aligned
        while (true) {
          if (result == Raw::NOT_FOUND || result % sizeof(T) == 0) {
            return result;
          } else {
            size_t newStart = result / sizeof(T) + 1;
            if (newStart >= start + dist) {
              return Raw::NOT_FOUND;
            }
            result = buf.find(&chunk,
                              sizeof(T),
                              newStart * sizeof(T),
                              (dist - (newStart - start)) * sizeof(T));
          }
        }
      }
    }
    
    void copy(const T *other, size_t size) {
      buf.copy(other, size * sizeof(T));
    }
    void copyTo(PrimView<T> &other, size_t dst, size_t src, size_t size) const {
      buf.copyTo(other.buf, dst * sizeof(T), src * sizeof(T), size * sizeof(T));
    }
    void copyTo(void *other, size_t src, size_t size) const {
      buf.copyTo(other, src * sizeof(T), size * sizeof(T));
    }
    void copyWithin(size_t src, size_t dst, size_t size) {
      buf.copyWithin(src * sizeof(T), dst * sizeof(T), size * sizeof(T));
    }
    
    inline T& operator[](size_t i) {
      return *(reinterpret_cast<T*>(buf.begin()) + i);
    }
    inline const T& operator[](size_t i) const {
      return *(reinterpret_cast<T*>(buf.begin()) + i);
    }
    
    inline size_t size() const {
      return buf.size() / sizeof(T);
    }
    inline void resize(size_t newSize, bool copy = false) {
      buf.resize(newSize * sizeof(T), copy);
    }
    inline T* begin() const {
      return reinterpret_cast<T*>(buf.begin());
    }
    inline T* end() const {
      return reinterpret_cast<T*>(buf.end());
    }
    
    Raw buf;
  };
  
  typedef PrimView<char> StringView;
  typedef PrimView<wchar_t> WStringView;
  
  typedef PrimView< uint8_t>  Uint8View;
  typedef PrimView<  int8_t>   Int8View;
  typedef PrimView<uint16_t> Uint16View;
  typedef PrimView< int16_t>  Int16View;
  typedef PrimView<uint32_t> Uint32View;
  typedef PrimView< int32_t>  Int32View;
  typedef PrimView<uint64_t> Uint64View;
  typedef PrimView< int64_t>  Int64View;
  
  typedef PrimView<float> Float32View;
  typedef PrimView<double> Float64View;
  typedef PrimView<long double> Float128View;
}

#endif