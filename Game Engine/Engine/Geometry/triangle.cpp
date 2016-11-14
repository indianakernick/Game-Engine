//
//  triangle.cpp
//  game engine
//
//  Created by Indi Kernick on 2/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "triangle.hpp"

Geometry::Triangle::Triangle(int ax, int ay, int bx, int by, int cx, int cy)
  : a(ax, ay), b(bx, by), c(cx, cy) {
  
}

Geometry::Triangle::Triangle(Point a, Point b, Point c)
  : a(a), b(b), c(c) {
  
}

std::ostream &operator<<(std::ostream &stream, Geometry::Triangle &tri) {
  return stream << "Triangle {" << tri.a << ", " << tri.b << ", " << tri.c << "}";
}

Geometry::Rect Geometry::Triangle::bounds() const {
  return Point::bounds({a, b, c});
}

Geometry::Point Geometry::Triangle::mid() const {
  return Point::mid({a, b, c});
}

Geometry::Triangle::Sides Geometry::Triangle::sides() const {
  return {{b,c}, {a,c}, {a,b}};
}
