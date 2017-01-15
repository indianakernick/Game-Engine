//
//  frustum.hpp
//  Game Engine
//
//  Created by Indi Kernick on 13/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_frustum_hpp
#define engine_3d_frustum_hpp

#include "plane.hpp"
#include "../Math/angleconstants.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Graphics3D {
  ///A projection matrix
  class Frustum {
  public:
    enum Side {
      NEAR,
      FAR,
      TOP,
      RIGHT,
      BOTTOM,
      LEFT
    };
    
    Frustum();
    Frustum(double fov, double aspect, double near, double far);
    
    const glm::mat4 &getMat() const;
    
    bool inside(const glm::vec3 &) const;
    bool inside(const glm::vec3 &, float) const;
    
    void set(double fov, double aspect, double near, double far);
    
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
    double fov = 60.0 * Math::DEG_RAD;
    double aspect = 16.0/9.0;
    double near = 1;
    double far = 1000;
    glm::mat4 mat;
  };
}

#endif
