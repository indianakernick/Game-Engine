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
#include <glm/gtx/euler_angles.hpp>

namespace Graphics3D {
  ///A model or view matrix
  class Transform {
  public:
    Transform() = default;
    explicit Transform(const glm::mat4 &);
    
    void setMat(const glm::mat4 &);
    const glm::mat4 &getMat() const;
    const glm::mat4 &getInvMat() const;
    
    //sets the position
    void moveTo(const glm::vec3 &);
    void moveTo(float, float, float);
    //adds the position
    void moveBy(const glm::vec3 &);
    void moveBy(float, float, float);
    const glm::vec3 &getPos() const;
    
    //sets the scale
    void scaleTo(const glm::vec3 &);
    void scaleTo(float, float, float);
    //multiplies the scale
    void scaleBy(const glm::vec3 &);
    void scaleBy(float, float, float);
    const glm::vec3 &getScale() const;
    
    //sets the rotation
    void rotateTo(float, float, float);
    void rotateYawTo(float);
    void rotatePitchTo(float);
    void rotateRollTo(float);
    //adds the rotation
    void rotateBy(float, float, float);
    void rotateYawBy(float);
    void rotatePitchBy(float);
    void rotateRollBy(float);
    
    glm::vec3 getRotation() const;
    float getYaw() const;
    float getPitch() const;
    float getRoll() const;
    
  private:
    glm::vec3 pos {0.0f, 0.0f, 0.0f};
    glm::vec3 scale {1.0f, 1.0f, 1.0f};
    float yaw = 0.0f;
    float pitch = 0.0f;
    float roll = 0.0f;
    
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
