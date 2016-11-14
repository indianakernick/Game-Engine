//
//  point.hpp
//  game engine
//
//  Created by Indi Kernick on 2/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef point_hpp
#define point_hpp

#include <vector>
#include "size.hpp"
#include <assert.h>
#include <string>
#include <random>
#include "dir.hpp"
#include <type_traits>

namespace Geometry {
  class Rect;
  
  class Point {
  public:
    Point() = default;
    Point(int x, int y);
    explicit Point(Size);
    ///Represent the object as a string for debug purposes
    std::string display() const;
    
    static Point rand();
    static Point rand(const Rect& bounds);
    static Point rand(const Size& size);
    
    Point operator+(const Point& other) const;
    Point operator-(const Point& other) const;
    Point operator+(const Size& other) const;
    Point operator-(const Size& other) const;
    //just learnt about type traits
    template <typename T>
    Point operator*(const T num) const {
      assert(std::is_arithmetic<T>::value);
      if (std::is_floating_point<T>::value) {
        assert(num != NAN && num != INFINITY && num != -INFINITY);
      }
      return {static_cast<int>(x * num),
              static_cast<int>(y * num)};
    }
    template <typename T>
    Point operator/(const T num) const {
      assert(std::is_arithmetic<T>::value);
      assert(num != 0);
      if (std::is_floating_point<T>::value) {
        assert(num != NAN && num != INFINITY && num != -INFINITY);
      }
      return {static_cast<int>(x * num),
              static_cast<int>(y * num)};
    }
    
    inline int toIndex(const Size& size) const {
      return y * size.w + x;
    }
    inline static Point fromIndex(const int index, const Size& size) {
      return {index % size.w,
              index / size.w};
    }
    ///Tests if x and y are both zero
    bool zero() const;
    ///Tests if the Point is within the Rect
    bool within(const Rect&) const;
    ///Tests if the Point is within the Size if the size is
    ///a Rect {0, 0, size.w, size.h}
    bool within(const Size&) const;
    ///Calculate the minimum Rect needed to enclose both Points
    static Rect bounds(const Point& a, const Point& b);
    ///Calculate the minimum Rect needed to enclose all the Points
    static Rect bounds(const std::vector<Point>& points);
    ///Calculate the Point which between both Points
    static Point mid(const Point& a, const Point& b);
    ///Calculate the Point which is the average of all the Points
    static Point mid(const std::vector<Point>& points);
    ///Calculate the distance between the Points
    static double dist(const Point& a, const Point& b);
    ///Calculate the pixel distance between the Points
    static int pxDist(const Point& a, const Point& b);
    
    ///Translate the point in the direction specified
    Point add(Dir, int = 1) const;
    ///Translate the point in the direction specified
    Point add(DirType, int = 1) const;
    
    static Point mul(Size, Dir, int = 1);
    static Point mul(Size, DirType, int = 1);
    
    bool operator==(const Point&) const;
    bool operator!=(const Point&) const;
    
    int x {0}, y {0};
  private:
    static std::random_device gen;
    static std::uniform_int_distribution<int> intDist;
  };
}

template<>
Geometry::Point Math::lerp(double, Geometry::Point, Geometry::Point);

#include "rect.hpp"

#endif
