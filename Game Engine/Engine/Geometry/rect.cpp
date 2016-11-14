//
//  rect.cpp
//  game engine
//
//  Created by Indi Kernick on 2/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "rect.hpp"

Geometry::Rect::Rect(int x, int y, int w, int h)
  : p(x,y), s(w,h) {
  
}

Geometry::Rect::Rect(Point p, Size s)
  : p(p), s(s) {
  
}

Geometry::Rect::Rect(Size size)
  : p(), s(size) {
  
}

std::ostream &operator<<(std::ostream &stream, Geometry::Rect &rect) {
  return stream << "Rect {" << rect.p << ", " << rect.s << "}";
}

Geometry::Point Geometry::Rect::mid() const {
  return {p.x + (s.w >> 1),
          p.y + (s.h >> 1)};
}

Geometry::Intercept Geometry::Rect::sideIntercept(const Geometry::Rect& a, const Geometry::Rect& b) {
  //the distance for each side the collision is in
  int dist[4] = {
    (b.p.y + b.s.h) - a.p.y,//top
    (a.p.x + a.s.w) - b.p.x,//right
    (a.p.y + a.s.h) - b.p.y,//bottom
    (b.p.x + b.s.w) - a.p.x//left
  };
  Intercept out;
  int minDist = INT_MAX;
  for (int i = 0; i < 4; i++) {
    if (dist[i] < minDist) {
      minDist = dist[i];
      out.side = static_cast<Side>(i);
    }
  }
  out.did = minDist > 0;
  return out;
}

Geometry::Intercept Geometry::Rect::sideIntercept(const Geometry::Rect& other) const {
  return sideIntercept(*this, other);
}

Geometry::Intercept Geometry::Rect::sideIntercept(const Geometry::Rect &a, const Geometry::Size &b) {
  return sideIntercept(a, static_cast<Rect>(b));
}

Geometry::Intercept Geometry::Rect::sideIntercept(const Geometry::Size &other) const {
  return sideIntercept(*this, other);
}

Geometry::Intercept Geometry::Rect::sideWithin(const Geometry::Rect& a, const Geometry::Rect& b) {
  //the distance for each side the collision is in
  int dist[4] = {
    b.p.y - a.p.y,
    (a.p.x + a.s.w) - (b.p.x + b.s.w),
    (a.p.y + a.s.h) - (b.p.y + b.s.h),
    b.p.x - a.p.x
  };
  Intercept out;
  int maxDist = INT_MIN;
  for (int i = 0; i < 4; i++) {
    if (dist[i] > maxDist) {
      maxDist = dist[i];
      out.side = static_cast<Side>(i);
    }
  }
  out.did = maxDist > 0;
  return out;
}

Geometry::Intercept Geometry::Rect::sideWithin(const Geometry::Rect& other) const {
  return sideWithin(*this, other);
}

Geometry::Intercept Geometry::Rect::sideWithin(const Geometry::Rect &a, const Geometry::Size &b) {
  return sideWithin(a, static_cast<Rect>(b));
}

Geometry::Intercept Geometry::Rect::sideWithin(const Geometry::Size &other) const {
  return sideWithin(*this, other);
}

bool Geometry::Rect::intercept(const Rect& a, const Rect& b) {
  return a.p.x < b.p.x + b.s.w &&
         a.p.y < b.p.y + b.s.h &&
         a.p.x + a.s.w > b.p.x &&
         a.p.y + a.s.h > b.p.y;
}

bool Geometry::Rect::intercept(const Rect& other) const {
  return intercept(*this, other);
}

bool Geometry::Rect::intercept(const Rect& a, const Size& b) {
  return a.p.x < b.w &&
         a.p.y < b.h &&
         a.p.x + a.s.w > 0 &&
         a.p.y + a.s.h > 0;
}

bool Geometry::Rect::intercept(const Size& other) const {
  return intercept(*this, other);
}

bool Geometry::Rect::within(const Rect& a, const Rect& b) {
  return a.p.x >= b.p.x &&
         a.p.y >= b.p.y &&
         a.p.x + a.s.w <= b.p.x + b.s.w &&
         a.p.y + a.s.h <= b.p.y + b.s.h;
}

bool Geometry::Rect::within(const Rect& other) const {
  return within(*this, other);
}

bool Geometry::Rect::within(const Rect& a, const Size& b) {
  return a.p.x >= 0 &&
         a.p.y >= 0 &&
         a.p.x + a.s.w <= b.w &&
         a.p.y + a.s.h <= b.h;
}

bool Geometry::Rect::within(const Size& other) const {
  return within(*this, other);
}

bool Geometry::Rect::operator==(const Rect& other) const {
  return p == other.p && s == other.s;
}

bool Geometry::Rect::operator!=(const Rect& other) const {
  return p != other.p || s != other.s;
}

bool Geometry::Rect::operator==(const Size& other) const {
  return p.zero() && s == other;
}

bool Geometry::Rect::operator!=(const Size& other) const {
  return !p.zero() || s != other;
}

template <>
Geometry::Rect Math::lerp(double t, Geometry::Rect from, Geometry::Rect to) {
  return {
    Math::lerp(t, from.p, to.p),
    Math::lerp(t, from.s, to.s)
  };
}
