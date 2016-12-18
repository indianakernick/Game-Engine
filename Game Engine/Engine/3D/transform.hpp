//
//  transform.hpp
//  Game Engine
//
//  Created by Indi Kernick on 7/09/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_transform_hpp
#define engine_3d_transform_hpp

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>

namespace Graphics3D {
  class Transform {
  public:
    Transform() = default;
    explicit Transform(const glm::mat4 &);
    
    void setMat(const glm::mat4 &);
    const glm::mat4 &getMat() const;
    const glm::mat4 &getInvMat() const;
    
    //sets the position
    void moveTo(const glm::vec3 &);
    //adds the position
    void moveBy(const glm::vec3 &);
    const glm::vec3 &getPos() const;
    
    //sets the scale
    void scaleTo(const glm::vec3 &);
    //multiplies the scale
    void scaleBy(const glm::vec3 &);
    const glm::vec3 &getScale() const;
    
    //sets the rotation
    void rotateTo(const glm::quat &);
    void rotateTo(float, const glm::vec3 &);
    //adds the rotation
    void rotateBy(const glm::quat &);
    void rotateBy(float, const glm::vec3 &);
    const glm::quat &getRotation() const;
    
  private:
    glm::vec3 pos;
    glm::vec3 scale {1, 1, 1};
    glm::quat rot;
    
    //they're mutable because they are potentially modified in getMat
    //and getInvMat
    mutable glm::mat4 mat;
    mutable glm::mat4 invMat;
    //set to true when the matrix needs to be recalculated
    mutable bool matChanged = false;
    
    void calcMat() const;
  };
}

#endif
