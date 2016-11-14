//
//  line.cpp
//  game engine
//
//  Created by Indi Kernick on 2/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "line.hpp"

Geometry::Line::Line(int ax, int ay, int bx, int by)
  : a(ax, ay), b(bx, by) {
  
}

Geometry::Line::Line(Point a, Point b)
  : a(a), b(b) {

}

std::string Geometry::Line::display() const {
  return "Line {" + a.display() + ", " + b.display() + "}";
}

Geometry::Point Geometry::Line::mid() const {
  return Point::mid(a, b);
}

Geometry::Rect Geometry::Line::bounds() const {
  return Point::bounds(a, b);
}

double Geometry::Line::length() const {
  return Point::dist(a, b);
}

int Geometry::Line::pxLength() const {
  return Point::pxDist(a, b);
}

bool Geometry::Line::vert() const {
  return a.x == b.x;
}

bool Geometry::Line::hori() const {
  return a.y == b.y;
}

Geometry::Line::Graph Geometry::Line::graph() const {
  Graph out;
  if (vert()) {
    out.valid = false;
  } else {
    out.m = static_cast<double>(a.y - b.y) / (a.x - b.x);
    out.b = -(out.m * a.x - a.y);
  }
  return out;
}

bool Geometry::Line::operator==(const Line& other) const {
  return a == other.a && b == other.b;
}

bool Geometry::Line::operator!=(const Line& other) const {
  return a != other.a || b != other.b;
}