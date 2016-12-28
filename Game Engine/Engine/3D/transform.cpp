//
//  transform.cpp
//  Game Engine
//
//  Created by Indi Kernick on 7/09/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "transform.hpp"

Graphics3D::Transform::Transform(const glm::mat4 &mat) {
  setMat(mat);
}

void Graphics3D::Transform::setMat(const glm::mat4 &newMat) {
  mat = newMat;
  invMat = glm::inverse(newMat);
  
  glm::quat rot;
  glm::vec3 skew;
  glm::vec4 perspective;
  
  glm::decompose(newMat, scale, rot, pos, skew, perspective);
  glm::extractEulerAngleXYZ(newMat, pitch, yaw, roll);
  matChanged = false;
}

const glm::mat4 &Graphics3D::Transform::getMat() const {
  calcMat();
  return mat;
}

const glm::mat4 &Graphics3D::Transform::getInvMat() const {
  calcMat();
  return invMat;
}

void Graphics3D::Transform::moveTo(const glm::vec3 &newPos) {
  pos = newPos;
  matChanged = true;
}

void Graphics3D::Transform::moveTo(float newX, float newY, float newZ) {
  pos = {newX, newY, newZ};
  matChanged = true;
}

void Graphics3D::Transform::moveBy(const glm::vec3 &delta) {
  pos += delta;
  matChanged = true;
}

void Graphics3D::Transform::moveBy(float deltaX, float deltaY, float deltaZ) {
  pos += glm::vec3(deltaX, deltaY, deltaZ);
  matChanged = true;
}

const glm::vec3 &Graphics3D::Transform::getPos() const {
  return pos;
}

void Graphics3D::Transform::scaleTo(const glm::vec3 &newScale) {
  scale = newScale;
  matChanged = true;
}

void Graphics3D::Transform::scaleTo(float newX, float newY, float newZ) {
  scale = {newX, newY, newZ};
  matChanged = true;
}

void Graphics3D::Transform::scaleBy(const glm::vec3 &multiple) {
  scale *= multiple;
  matChanged = true;
}

void Graphics3D::Transform::scaleBy(float mulX, float mulY, float mulZ) {
  scale *= glm::vec3(mulX, mulY, mulZ);
  matChanged = true;
}

const glm::vec3 &Graphics3D::Transform::getScale() const {
  return scale;
}

void Graphics3D::Transform::rotateTo(float newYaw, float newPitch, float newRoll) {
  yaw = newYaw;
  pitch = newPitch;
  roll = newRoll;
  matChanged = true;
}

void Graphics3D::Transform::rotateYawTo(float newYaw) {
  yaw = newYaw;
  matChanged = true;
}

void Graphics3D::Transform::rotatePitchTo(float newPitch) {
  pitch = newPitch;
  matChanged = true;
}

void Graphics3D::Transform::rotateRollTo(float newRoll) {
  roll = newRoll;
  matChanged = true;
}

void Graphics3D::Transform::rotateBy(float deltaYaw, float deltaPitch, float deltaRoll) {
  yaw += deltaYaw;
  pitch += deltaPitch;
  roll += deltaRoll;
  matChanged = true;
}

void Graphics3D::Transform::rotateYawBy(float deltaYaw) {
  yaw += deltaYaw;
  matChanged = true;
}

void Graphics3D::Transform::rotatePitchBy(float deltaPitch) {
  pitch += deltaPitch;
  matChanged = true;
}

void Graphics3D::Transform::rotateRollBy(float deltaRoll) {
  roll += deltaRoll;
  matChanged = true;
}

glm::vec3 Graphics3D::Transform::getRotation() const {
  return {yaw, pitch, roll};
}

float Graphics3D::Transform::getYaw() const {
  return yaw;
}

float Graphics3D::Transform::getPitch() const {
  return pitch;
}

float Graphics3D::Transform::getRoll() const {
  return roll;
}

void Graphics3D::Transform::calcMat() const {
  if (matChanged) {
    //RST rotation scale translation
    mat = glm::scale(glm::translate({}, pos) * glm::eulerAngleYXZ(yaw, pitch, roll), scale);
    invMat = glm::inverse(mat);
    matChanged = false;
  }
}
