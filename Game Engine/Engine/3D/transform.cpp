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
  glm::vec3 skew;
  glm::vec4 perspective;
  glm::decompose(newMat, scale, rot, pos, skew, perspective);
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

void Graphics3D::Transform::moveBy(const glm::vec3 &delta) {
  pos += delta;
  matChanged = true;
}

const glm::vec3 &Graphics3D::Transform::getPos() const {
  return pos;
}

void Graphics3D::Transform::scaleTo(const glm::vec3 &newScale) {
  scale = newScale;
  matChanged = true;
}

void Graphics3D::Transform::scaleBy(const glm::vec3 &multiple) {
  scale *= multiple;
  matChanged = true;
}

const glm::vec3 &Graphics3D::Transform::getScale() const {
  return scale;
}

void Graphics3D::Transform::rotateTo(const glm::quat &newRot) {
  rot = newRot;
  matChanged = true;
}

void Graphics3D::Transform::rotateTo(float angle, const glm::vec3 &axis) {
  glm::quat identity;
  rot = glm::rotate(identity, angle, axis);
  matChanged = true;
}

void Graphics3D::Transform::rotateBy(const glm::quat &delta) {
  //delta doesn't seem like the right name but it sort of makes sense...
  rot *= delta;
  matChanged = true;
}

void Graphics3D::Transform::rotateBy(float angle, const glm::vec3 &axis) {
  rot = glm::rotate(rot, angle, axis);
  matChanged = true;
}

const glm::quat &Graphics3D::Transform::getRotation() const {
  return rot;
}

void Graphics3D::Transform::calcMat() const {
  if (matChanged) {
    //RST rotation scale translation
    mat = glm::translate(glm::scale(glm::mat4_cast(rot), scale), pos);
    invMat = glm::inverse(mat);
    matChanged = false;
  }
}
