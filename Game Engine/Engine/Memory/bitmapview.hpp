//
//  bitmapview.hpp
//  Game Engine
//
//  Created by Indi Kernick on 27/09/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_memory_bitmapview_hpp
#define engine_memory_bitmapview_hpp

#include "buffer.hpp"
#include <Geometry/rect.hpp>

namespace Memory {
  template<typename T>
  class BitmapView {
  public:
    BitmapView(Buffer &buf, Geometry::Size size)
      : buf(buf), size(size) {
      assert(buf.size() == size.area() * sizeof(T));
    }
    explicit BitmapView(Geometry::Size size)
      : buf(size.area() * sizeof(T)), size(size) {}
    BitmapView(Geometry::Size size, const T &chunk)
      : buf(size.area() * sizeof(T)), size(size) {
      fill(chunk);
    }
    BitmapView(const BitmapView<T> &) = default;
    BitmapView(BitmapView<T> &&) = default;
    ~BitmapView() = default;
    
    BitmapView<T>& operator=(const BitmapView<T> &) = default;
    BitmapView<T>& operator=(BitmapView<T> &&) = default;
    
    bool operator==(const BitmapView<T> &other) const {
      return size == other.size && buf == other.buf;
    }
    bool operator!=(const BitmapView<T> &other) const {
      return size != other.size || buf != other.buf;
    }
    
    void fill(const T &chunk) {
      buf.fill(&chunk, sizeof(T));
    }
    void fill(const Geometry::Rect &rect, const T &chunk) {
      assert(rect.within(size));
      if (rect == size) {
        buf.fill(&chunk, sizeof(T));
      } else {
        Geometry::Point start = rect.p;
        int end = start.y + rect.s.h;
        for (; start.y < end; start.y++) {
          buf.fill(&chunk,
                   sizeof(T),
                   start.toIndex(size) * sizeof(T),
                   rect.s.w * sizeof(T));
        }
      }
    }
    
    static const Geometry::Point NOT_FOUND;
    
    Geometry::Point find(const T &chunk) {
      if (sizeof(T) == 1) {
        return buf.find(reinterpret_cast<Byte>(chunk));
      } else {
        size_t result = buf.find(&chunk, sizeof(T));
        while (true) {
          if (result == Buffer::NOT_FOUND) {
            break;
          } else if (result % sizeof(T) == 0) {
            return Geometry::Point::fromIndex(result, size);
          } else {
            size_t newStart = result / sizeof(T) + 1;
            if (newStart >= buf.size()) {
              break;
            }
            result = buf.find(&chunk,
                              sizeof(T),
                              newStart * sizeof(T),
                              (buf.size() - newStart) * sizeof(T));
          }
        }
        return NOT_FOUND;
      }
    }
    
    Geometry::Point find(const T &chunk, const Geometry::Rect &area) {
      if (area.s.neg() || (area.p.zero() && area.s == size)) {
        return find(chunk);
      } else {
        Geometry::Point start = area.p;
        int end = start.y + area.s.h;
        for (; start.y < end; start.y++) {
          size_t startI = start.toIndex(size);
          size_t result = buf.find(&chunk,
                                   sizeof(T),
                                   startI * sizeof(T),
                                   area.s.w * sizeof(T));
          while (true) {
            if (result == Buffer::NOT_FOUND) {
              break;
            } else if (result % sizeof(T) == 0) {
              return Geometry::Point::fromIndex(result, size);
            } else {
              size_t newStart = (result / sizeof(T) + 1);
              if (newStart >= startI + area.s.w) {
                break;
              }
              result = buf.find(&chunk,
                                sizeof(T),
                                newStart * sizeof(T),
                                (area.s.w - (newStart - startI)) * sizeof(T));
            }
          }
        }
        return NOT_FOUND;
      }
    }
    
    void copy(const BitmapView<T> &other) {
      size = other.size;
      buf.copy(other.buf);
    }
    
    void copyWithin(const Geometry::Rect &source, const Geometry::Rect &dest) {
      assert(source.within(size));
      assert(source.within(dest));
      assert(source.s == dest.s);
      Geometry::Point sourceStart = source.p;
      Geometry::Point destStart = dest.p;
      for (; sourceStart.y < source.s.h; sourceStart.y++, destStart.y++) {
        buf.copyWithin(sourceStart.toIndex(size) * sizeof(T),
                       destStart.toIndex(size) * sizeof(T),
                       source.s.w * sizeof(T));
      }
    }
    
    inline T& operator()(int x, int y) {
      assert(x < size.w);
      assert(y < size.h);
      return *(reinterpret_cast<T*>(buf.begin()) + y * size.w + x);
    }
    inline const T& operator()(int x, int y) const {
      assert(x < size.w);
      assert(y < size.h);
      return *(reinterpret_cast<T*>(buf.begin()) + y * size.w + x);
    }
    inline T& operator()(Geometry::Point p) {
      assert(p.within(size));
      return *(reinterpret_cast<T*>(buf.begin()) + p.toIndex(size));
    }
    inline const T& operator()(Geometry::Point p) const {
      assert(p.within(size));
      return *(reinterpret_cast<T*>(buf.begin()) + p.toIndex(size));
    }
    
    inline Geometry::Size getSize() {
      return size;
    }
    inline int getWidth() {
      return size.w;
    }
    inline int getHeight() {
      return size.h;
    }
    
    Buffer buf;
  private:
    Geometry::Size size;
  };
  
  typedef BitmapView<uint32_t> Uint32Bitmap;
  typedef BitmapView<float> Float32Bitmap;
  typedef BitmapView<double> Float64Bitmap;
  typedef BitmapView<long double> Float128Bitmap;
}

#endif
