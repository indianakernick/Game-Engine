//
//  rect.hpp
//  Game Engine
//
//  Created by Indi Kernick on 2/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_geometry_rect_hpp
#define engine_geometry_rect_hpp

#include "size.hpp"
#include "point.hpp"
#include <string>

namespace Geometry {
  enum class Side : unsigned char;
  
  struct Intercept {
    bool did;
    Side side;
  };

  class Rect {
  public:
    Rect() = default;
    Rect(int x, int y, int w, int h);
    Rect(Point p, Size s);
    explicit Rect(Size);
    
    friend std::ostream &operator<<(std::ostream &stream, const Rect &rect);
    friend std::ostream &operator<<(std::ostream &stream, const Rect &&rect);
    
    Point mid() const;
    
    int top() const;
    int right() const;
    int bottom() const;
    int left() const;
    int side(Side) const;
    
    ///Tests if two rectangles intercept with each other and
    ///determines which side of the first rect the second is on
    static Intercept sideIntercept(const Rect&, const Rect&);
    ///Tests if two rectangles intercept with each other and
    ///determines which side of the first rect the second is on
    Intercept sideIntercept(const Rect&) const;
    
    ///Tests if two rectangles intercept with each other and
    ///determines which side of the first rect the second is on
    static Intercept sideIntercept(const Rect&, const Size&);
    ///Tests if two rectangles intercept with each other and
    ///determines which side of the first rect the second is on
    Intercept sideIntercept(const Size&) const;
    
    ///Tests if the first rect is entirly within the second and
    ///determines which side of the first rect the second is on
    static Intercept sideWithin(const Rect&, const Rect&);
    ///Tests if the first rect is entirly within the second and
    ///determines which side of the first rect the second is on
    Intercept sideWithin(const Rect&) const;
    
    ///Tests if the first rect is entirly within the second and
    ///determines which side of the first rect the second is on
    static Intercept sideWithin(const Rect&, const Size&);
    ///Tests if the first rect is entirly within the second and
    ///determines which side of the first rect the second is on
    Intercept sideWithin(const Size&) const;
    
    ///Tests if two rectangles intercept with each other
    static bool intercept(const Rect&, const Rect&);
    ///Tests if two rectangles intercept with each other
    bool intercept(const Rect&) const;
    
    ///Tests if two rectangles intercept with each other
    static bool intercept(const Rect&, const Size&);
    ///Tests if two rectangles intercept with each other
    bool intercept(const Size&) const;
    
    ///Tests if the first rectangle is entirly within the second
    static bool within(const Rect&, const Rect&);
    ///Tests if the first rectangle is entirly within the second
    bool within(const Rect&) const;
    
    ///Tests if the first rectangle is entirly within the second
    static bool within(const Rect&, const Size&);
    ///Tests if the first rectangle is entirly within the second
    bool within(const Size&) const;
    
    bool operator== (const Rect&) const;
    bool operator!= (const Rect&) const;
    
    bool operator== (const Size&) const;
    bool operator!= (const Size&) const;
    
    Point p;
    Size s;
  };
};

template <>
struct std::is_arithmetic<Geometry::Rect> {
  static const bool value = true;
};

template <>
Geometry::Rect Math::lerp(double, Geometry::Rect, Geometry::Rect);

#include "dir.hpp"

#endif
