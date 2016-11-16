//
//  point.cpp
//  game engine
//
//  Created by Indi Kernick on 2/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "point.hpp"

using namespace Geometry;

std::random_device Point::gen;
std::uniform_int_distribution<int> Point::intDist(INT_MIN, INT_MAX);

Point::Point(int x, int y)
  : x(x), y(y) {
  
}

Point::Point(Size size)
  : x(size.w), y(size.h) {

}

std::ostream &Geometry::operator<<(std::ostream &stream, Geometry::Point &point) {
  return stream << "Point {" << point.x << ", " << point.y << "}";
}

Point Point::rand() {
  return {intDist(gen), intDist(gen)};
}

Point Point::rand(const Rect& bounds) {
  assert(!bounds.s.zero());
  std::uniform_int_distribution<int> distX(0,bounds.s.w > 0 ? bounds.s.w - 1
                                                            : bounds.s.w + 1);
  std::uniform_int_distribution<int> distY(0,bounds.s.h > 0 ? bounds.s.h - 1
                                                            : bounds.s.h + 1);
  return {bounds.p.x + distX(gen), bounds.p.y + distY(gen)};
}

Point Point::rand(const Size& size) {
  assert(!size.zero());
  std::uniform_int_distribution<int> distX(0,size.w > 0 ? size.w - 1
                                                        : size.w + 1);
  std::uniform_int_distribution<int> distY(0,size.h > 0 ? size.h - 1
                                                        : size.h + 1);
  return {distX(gen), distY(gen)};
}

Point Point::operator+(const Point& other) const {
  return {x + other.x, y + other.y};
}

Point Point::operator-(const Point& other) const {
  return {x - other.x, y - other.y};
}

Point Point::operator+(const Size& other) const {
  return {x + other.w, y + other.h};
}

Point Point::operator-(const Size& other) const {
  return {x - other.w, y - other.h};
}

bool Point::zero() const {
  return x == 0 && y == 0;
}

bool Point::within(const Rect& r) const {
  return x >= r.p.x && x < r.p.x + r.s.w &&
         y >= r.p.y && y < r.p.y + r.s.h;
}

bool Point::within(const Size& s) const {
  return x >= 0 && y >= 0 &&
         x < s.w && y < s.h;
}

Rect Point::bounds(const Point& a, const Point& b) {
  int minX = a.x < b.x ? a.x : b.x;
  int minY = a.y < b.y ? a.y : b.y;
  int maxX = a.x > b.x ? a.x : b.x;
  int maxY = a.y > b.y ? a.y : b.y;
  return {minX,
          minY,
          maxX - minX + 1,
          maxY - minY + 1};
}

Rect Point::bounds(const std::vector<Point>& points) {
  if (points.size() > 0) {
    Point min = points[0], max = points[0];
    
    for (size_t i = 0; i < points.size(); i++) {
      min.x = points[i].x < min.x ? points[i].x : min.x;
      min.y = points[i].y < min.y ? points[i].y : min.y;
      max.x = points[i].x > max.x ? points[i].x : max.x;
      max.y = points[i].y > max.y ? points[i].y : max.y;
    }
    
    return {min.x,
            min.y,
            max.x - min.x + 1,
            max.y - min.y + 1};
  } else {
    return {};
  }
}

Point Point::mid(const Point& a, const Point& b) {
  return {(a.x + b.x) >> 1,
          (a.y + b.y) >> 1};
}

Point Point::mid(const std::vector<Point>& points) {
  if (points.size() > 0) {
    Point sum;
    for (size_t i = 0; i < points.size(); i++) {
      sum.x += points[i].x;
      sum.y += points[i].y;
    }
    return {static_cast<int>(sum.x / points.size()),
            static_cast<int>(sum.y / points.size())};
  } else {
    return {};
  }
}

double Point::dist(const Point& a, const Point& b) {
  int dx = a.x - b.x;
  int dy = a.y - b.y;
  return sqrt(dx * dx + dy * dy);
}

int Point::pxDist(const Point& a, const Point& b) {
  int dx = a.x > b.x ? a.x - b.x : b.x - a.x;
  int dy = a.y > b.y ? a.y - b.y : b.y - a.y;
  return dx > dy ? dx : dy;
}

Point Point::add(Dir dir, int dist) const {
  switch (dir) {
    case Dir::UP:
      return {x, y - dist};
    case Dir::RIGHT:
      return {x + dist, y};
    case Dir::DOWN:
      return {x, y + dist};
    case Dir::LEFT:
      return {x - dist, y};
  }
}

Point Point::add(DirType dir, int dist) const {
  validate(dir);
  switch (dir) {
    case 0:
      return {x, y - dist};
    case 1:
      return {x + dist, y};
    case 2:
      return {x, y + dist};
    case 3:
      return {x - dist, y};
    default://won't happen
      return {};
  }
}

Geometry::Point Geometry::Point::mul(Size size, Dir dir, int num) {
  if (num == 0) {
    return {0, 0};
  }
  
  switch (dir) {
    case Dir::UP:
      return {0, -size.h * num};
    case Dir::RIGHT:
      return {size.w * num, 0};
    case Dir::DOWN:
      return {0, size.h * num};
    case Dir::LEFT:
      return {-size.w * num, 0};
  }
}

Geometry::Point Geometry::Point::mul(Size size, DirType dir, int num) {
  if (num == 0) {
    return {0, 0};
  }
  
  validate(dir);
  switch (dir) {
    case 0:
      return {0, -size.h * num};
    case 1:
      return {size.w * num, 0};
    case 2:
      return {0, size.h * num};
    case 3:
      return {-size.w * num, 0};
    default://won't happen
      return {};
  }
}

bool Point::operator==(const Point& other) const {
  return x == other.x && y == other.y;
}

bool Point::operator!=(const Point& other) const {
  return x != other.x || y != other.y;
}

template<>
Geometry::Point Math::lerp(double t, Geometry::Point from, Geometry::Point to) {
  return {
    Math::lerp(t, from.x, to.x),
    Math::lerp(t, from.y, to.y)
  };
}
