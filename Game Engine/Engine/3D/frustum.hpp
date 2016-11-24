//
//  frustum.hpp
//  Game Engine
//
//  Created by Indi Kernick on 13/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef frustum_hpp
#define frustum_hpp

/*#include "plane.hpp"

class Frustum {
public:
  enum Side : char {
    NEAR = 0,
    FAR,
    TOP,
    RIGHT,
    BOTTOM,
    LEFT
  };
  
  Frustum();
  
  Frustum(double fov, double aspect, double near, double far);
  
  Frustum(const Frustum &) = default;
  Frustum(Frustum &&) = default;
  ~Frustum() = default;
  
  Frustum &operator=(const Frustum &) = default;
  Frustum &operator=(Frustum &&) = default;
  
  Mat44 getMat();
  
  bool inside(const Vec3 &) const;
  
  void set(double fov, double aspect, double near, double far);
  void get(double &fov, double &aspect, double &near, double &far) const;
  
  void setFOV(double newFov);
  void setAspect(double newAspect);
  void setNear(double newNear);
  void setFar(double newFar);
  
  double getFOV() const;
  double getAspect() const;
  double getNear() const;
  double getFar() const;
  
private:
  Plane planes[6];
  double fov = Math::PId2;//90 deg
  double aspect = 1;
  double near = 1;
  double far = 1000;
};*/

#endif
