//
//  plane.hpp
//  Game Engine
//
//  Created by Indi Kernick on 13/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_plane_hpp
#define engine_3d_plane_hpp

#include <glm/glm.hpp>

class Plane {
public:
  Plane() = default;
  ///Assumes counter-clockwise order
  Plane(const glm::vec3 &v0, const glm::vec3 &v1, const glm::vec3 &v2);
  Plane(const glm::vec3 &point, const glm::vec3 &normal);
  Plane(float a, float b, float c, float d);
  
  void unit();
  bool isUnit() const;
  ///Assumes this is a unit plane
  float dist(const glm::vec3 &) const;
  ///Assumes this is a unit plane
  bool onPlane(const glm::vec3 &, float tolerance = 0.01) const;
  ///Inside is toward the direction of the normal (Assumes this is a unit plane)
  bool inside(const glm::vec3 &) const;
  ///Inside is toward the direction of the normal (Assumes this is a unit plane)
  bool inside(const glm::vec3 &, float) const;
  
  float a = 1;
  float b = 0;
  float c = 0;
  float d = 0;
};

#endif
