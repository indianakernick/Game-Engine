//
//  size.hpp
//  Game Engine
//
//  Created by Indi Kernick on 2/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef size_hpp
#define size_hpp

#include <assert.h>
#include <string>
#include <math.h>
#include "../Math/interpolate.hpp"
#include <iostream>

namespace Geometry {
  class Size {
  public:
    Size() = default;
    Size(int w, int h);
    
    friend std::ostream &operator<<(std::ostream &stream, Geometry::Size &size);
    
    Size operator+(const Size& other) const;
    Size operator-(const Size& other) const;
    template <typename T>
    Size operator*(const T num) const {
      assert(std::is_arithmetic<T>::value);
      if (std::is_floating_point<T>::value) {
        assert(num != NAN && num != INFINITY && num != -INFINITY);
      }
      return {static_cast<int>(w * num),
              static_cast<int>(h * num)};
    }
    template <typename T>
    Size operator/(const T num) const {
      assert(std::is_arithmetic<T>::value);
      assert(num != 0);
      if (std::is_floating_point<T>::value) {
        assert(num != NAN && num != INFINITY && num != -INFINITY);
      }
      return {static_cast<int>(w * num),
              static_cast<int>(h * num)};
    }
    
    ///Calculate the area
    inline int area() const {
      return w * h;
    }
    ///Test if either dimension is zero
    inline bool zero() const {
      return w == 0 || h == 0;
    }
    ///Test if either dimension is negative
    inline bool neg() const {
      return w < 0 || h < 0;
    }
    ///Test if both dimensions are zero
    inline bool zero2() const {
      return w == 0 && h == 0;
    }
    ///Test if both dimensions are negative
    inline bool neg2() const {
      return w < 0 && h < 0;
    }
    ///Test if both dimensions are equal and therefore square
    inline bool square() const {
      return w == h;
    }
    
    bool operator==(const Size&) const;
    bool operator!=(const Size&) const;
    
    int w {0}, h {0};
  };
}

template <>
struct std::is_arithmetic<Geometry::Size> {
  static const bool value = true;
};

template<>
Geometry::Size Math::lerp(double, Geometry::Size, Geometry::Size);

#endif
