//
//  plane.hpp
//  Game Engine
//
//  Created by Indi Kernick on 13/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef plane_hpp
#define plane_hpp

/*#include "vec3.hpp"

class Plane {
public:
  Plane() = default;
  ///Assumes counter-clockwise order
  Plane(const Vec3 &v0, const Vec3 &v1, const Vec3 &v2);
  Plane(const Vec3 &point, const Vec3 &normal);
  Plane(double a, double b, double c, double d);
  
  Plane(const Plane &) = default;
  Plane(Plane &&) = default;
  ~Plane() = default;
  
  Plane &operator=(const Plane &) = default;
  Plane &operator=(Plane &&) = default;
  
  void unit();
  bool isUnit() const;
  ///Assumes this is a unit plane
  double dist(const Vec3 &) const;
  ///Assumes this is a unit plane
  bool onPlane(const Vec3 &, double tolerance = 0.001) const;
  ///Inside is toward the direction of the normal (Assumes this is a unit plane)
  bool inside(const Vec3 &) const;
  
  double a = 1;
  double b = 0;
  double c = 0;
  double d = 0;
};*/

#endif
