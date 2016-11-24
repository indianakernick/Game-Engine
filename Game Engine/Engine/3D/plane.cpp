//
//  plane.cpp
//  Game Engine
//
//  Created by Indi Kernick on 13/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "plane.hpp"

/*Plane::Plane(const Vec3 &v0, const Vec3 &v1, const Vec3 &v2) {
  Vec3 v0tov1 = v1 - v0;
  v0tov1.unit();
  Vec3 v0tov2 = v2 - v0;
  v0tov2.unit();
  Vec3 normal = v0tov1.cross(v0tov2);
  a = normal.x;
  b = normal.y;
  c = normal.z;
  Vec3 unit0 = v0;
  unit0.unit();
  d = unit0.dot(normal) * v0.getMag();
}

Plane::Plane(const Vec3 &point, const Vec3 &normal)
  : a(normal.x), b(normal.y), c(normal.z), d(point.getMag()) {
  assert(normal.isUnit());
}

Plane::Plane(double a, double b, double c, double d)
  : a(a), b(b), c(c), d(d) {}

void Plane::unit() {
  double mag = sqrt(a*a + b*b + c*c);
  a /= mag;
  b /= mag;
  c /= mag;
  d /= mag;
}

bool Plane::isUnit() const {
  return a*a + b*b + c*c == 1;
}

double Plane::dist(const Vec3 &point) const {
  return a*point.x + b*point.y + c*point.z + d;
}

bool Plane::onPlane(const Vec3 &point, double tolerance) const {
  assert(tolerance >= 0);
  return fabs(dist(point)) <= tolerance;
}

bool Plane::inside(const Vec3 &point) const {
  return dist(point) >= 0;
}*/
