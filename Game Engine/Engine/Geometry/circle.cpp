//
//  circle.cpp
//  Game Engine
//
//  Created by Indi Kernick on 2/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "circle.hpp"

Geometry::Circle::Circle(int cx, int cy, int r)
  : c(cx, cy), r(r) {
  
}

Geometry::Circle::Circle(Point c, int r)
  : c(c), r(r) {
  
}

std::ostream &Geometry::operator<<(std::ostream &stream, const Geometry::Circle &circle) {
  return stream << "Circle {" << circle.c << ", " << circle.r << "}";
}

std::ostream &Geometry::operator<<(std::ostream &stream, const Geometry::Circle &&circle) {
  return stream << "Circle {" << circle.c << ", " << circle.r << "}";
}

Geometry::Rect Geometry::Circle::bounds() const {
  return {c.x - r,
          c.y - r,
          (r << 1),
          (r << 1)};
}
