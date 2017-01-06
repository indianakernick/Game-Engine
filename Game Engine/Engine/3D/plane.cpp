//
//  plane.cpp
//  Game Engine
//
//  Created by Indi Kernick on 13/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "plane.hpp"

#include <glm/glm.hpp>

Plane::Plane(const glm::vec3 &v0, const glm::vec3 &v1, const glm::vec3 &v2) {
  glm::vec3 v0tov1 = glm::normalize(v1 - v0);
  glm::vec3 v0tov2 = glm::normalize(v2 - v0);
  glm::vec3 normal = glm::cross(v0tov1, v0tov2);
  a = normal.x;
  b = normal.y;
  c = normal.z;
  d = glm::dot(glm::normalize(v0), normal) * v0.length();
}

Plane::Plane(const glm::vec3 &point, const glm::vec3 &normal)
  : a(normal.x), b(normal.y), c(normal.z), d(glm::length(point)) {
  assert(0.999 <= std::fabsf(glm::length(normal)) && std::fabsf(glm::length(normal)) <= 1.001);
}

Plane::Plane(float a, float b, float c, float d)
  : a(a), b(b), c(c), d(d) {}

void Plane::unit() {
  float mag = std::sqrtf(a*a + b*b + c*c);
  a /= mag;
  b /= mag;
  c /= mag;
  d /= mag;
}

bool Plane::isUnit() const {
  return a*a + b*b + c*c == 1;
}

float Plane::dist(const glm::vec3 &point) const {
  return a*point.x + b*point.y + c*point.z + d;
}

bool Plane::onPlane(const glm::vec3 &point, float tolerance) const {
  assert(tolerance >= 0);
  return std::fabsf(dist(point)) <= tolerance;
}

bool Plane::inside(const glm::vec3 &point) const {
  return dist(point) >= 0;
}

bool Plane::inside(const glm::vec3 &point, float radius) const {
  return dist(point) >= -radius;
}
