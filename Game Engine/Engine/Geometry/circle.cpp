//
//  circle.cpp
//  game engine
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

std::string Geometry::Circle::display() const {
  return "Circle {" + c.display() + ", " + std::to_string(r) + "}";
}

Geometry::Rect Geometry::Circle::bounds() const {
  return {c.x - r,
          c.y - r,
          (r << 1),
          (r << 1)};
}