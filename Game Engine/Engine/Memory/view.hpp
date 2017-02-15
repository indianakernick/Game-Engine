//
//  view.hpp
//  Game Engine
//
//  Created by Indi Kernick on 26/09/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_memory_view_hpp
#define engine_memory_view_hpp

#include "buffer.hpp"
#include <utility>

namespace Memory {
  ///A Primitive type memory view. For types that don't need their
  ///constructors and destructors called
  template <typename T>
  class View {
  public:
    explicit View(Buffer &other)
      : buf(other) {
      assert(other.size() % sizeof(T) == 0);
    }
    explicit View(const size_t size)
      : buf(size * sizeof(T)) {}
    View(void *data, const size_t size, Assign assign = MOVE)
      : buf(data, size, assign) {}
    View(const size_t size, const T chunk)
      : buf(size * sizeof(T)) {
      fill(chunk);
    }
    View(const View<T> &) = default;
    View(View<T> &&) = default;
    ~View() {
      static_assert(std::is_pod<T>::value, "Memory::View can only handle POD types. Use std::vector<> for non-POD types");
    };
    
    View<T> &operator=(const View<T> &) = default;
    View<T> &operator=(View<T> &&) = default;
    
    bool operator==(const View<T> &other) const {
      return buf == other.buf;
    }
    bool operator!=(const View<T> &other) const {
      return buf != other.buf;
    }
    
    void fill(const T chunk, size_t start = 0, size_t dist = 0) {
      buf.fill(&chunk, sizeof(T), start * sizeof(T), dist * sizeof(T));
    }
    
    size_t find(const T chunk, size_t start = 0, size_t dist = 0) const {
      if (sizeof(T) == 1) {
        return buf.find(*reinterpret_cast<Byte *>(&chunk), start, dist);
      } else {
        size_t result = buf.find(&chunk,
                                 sizeof(T),
                                 start * sizeof(T),
                                 dist * sizeof(T));
        //we have to make sure that the result is aligned because memmem
        //finds ANY substring in the string not just the substrings that
        //are aligned
        while (true) {
          if (result == Buffer::NOT_FOUND || result % sizeof(T) == 0) {
            return result;
          } else {
            size_t newStart = result / sizeof(T) + 1;
            if (newStart >= start + dist) {
              return Buffer::NOT_FOUND;
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
    void copyTo(View<T> &other, size_t dst, size_t src, size_t size) const {
      buf.copyTo(other.buf, dst * sizeof(T), src * sizeof(T), size * sizeof(T));
    }
    void copyTo(void *other, size_t src, size_t size) const {
      buf.copyTo(other, src * sizeof(T), size * sizeof(T));
    }
    void copyWithin(size_t src, size_t dst, size_t size) {
      buf.copyWithin(src * sizeof(T), dst * sizeof(T), size * sizeof(T));
    }
    
    inline T& operator[](size_t i) {
      return *(buf.begin<T>() + i);
    }
    inline const T& operator[](size_t i) const {
      return *(buf.cbegin<T>() + i);
    }
    
    inline size_t size() const {
      return buf.size() / sizeof(T);
    }
    inline void resize(size_t newSize, bool copy = false) {
      buf.resize(newSize * sizeof(T), copy);
    }
    
    inline T *begin() {
      return buf.begin<T>();
    }
    inline T *end() {
      return buf.end<T>();
    }
    inline const T *begin() const {
      return buf.cbegin<T>();
    }
    inline const T *end() const {
      return buf.cend<T>();
    }
    inline const T *cbegin() const {
      return buf.cbegin<T>();
    }
    inline const T *cend() const {
      return buf.cend<T>();
    }
    
    Buffer buf;
  };
  
  using StringView = View<char>;
  using WStringView = View<wchar_t>;
  
  using Uint8View  = View< uint8_t>;
  using Int8View   = View<  int8_t>;
  using Uint16View = View<uint16_t>;
  using Int16View  = View< int16_t>;
  using Uint32View = View<uint32_t>;
  using Int32View  = View< int32_t>;
  using Uint64View = View<uint64_t>;
  using Int64View  = View< int64_t>;
  
  using Float32View  = View<float>;
  using Float64View  = View<double>;
  using Float128View = View<long double>;
}

#endif
