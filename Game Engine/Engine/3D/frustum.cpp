//
//  frustum.cpp
//  Game Engine
//
//  Created by Indi Kernick on 13/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "frustum.hpp"

Graphics3D::Frustum::Frustum() {
  set(fov, aspect, near, far);
}

Graphics3D::Frustum::Frustum(double fov, double aspect, double near, double far) {
  set(fov, aspect, near, far);
}

const glm::mat4 &Graphics3D::Frustum::getMat() const {
  return mat;
}

bool Graphics3D::Frustum::inside(const glm::vec3 &point) const {
  for (int i = 0; i < 6; i++) {
    if (!planes[i].inside(point)) {
      return false;
    }
  }
  return true;
}

bool Graphics3D::Frustum::inside(const glm::vec3 &point, float radius) const {
  for (int i = 0; i < 6; i++) {
    if (!planes[i].inside(point, radius)) {
      return false;
    }
  }
  return true;
}

void Graphics3D::Frustum::set(double fov, double aspect, double near, double far) {
  assert(fov > 0);
  assert(fov < Math::PI);
  assert(aspect > 0);
  assert(near > 0);
  assert(far > 0);
  assert(far > near);
  
  this->fov = fov;
  this->aspect = aspect;
  this->near = near;
  this->far = far;
  
  mat = glm::perspective(fov, aspect, near, far);
  
  double tanFovD2 = tan(fov / 2);
  
  double nearHeightD2 = near * tanFovD2;
  double nearWidthD2 = nearHeightD2 * aspect;
  double farHeightD2 = far * tanFovD2;
  double farWidthD2 = farHeightD2 * aspect;
  
  glm::vec3 nearTopRight(nearWidthD2,nearHeightD2,near);
  glm::vec3 nearBotRight(nearWidthD2,-nearHeightD2,near);
  glm::vec3 nearBotLeft(-nearWidthD2,-nearHeightD2,near);
  glm::vec3 nearTopLeft(-nearWidthD2,nearHeightD2,near);
  
  glm::vec3 farTopRight(farWidthD2,farHeightD2,far);
  glm::vec3 farBotRight(farWidthD2,-farHeightD2,far);
  glm::vec3 farBotLeft(-farWidthD2,-farHeightD2,far);
  glm::vec3 farTopLeft(-farWidthD2,farHeightD2,far);
  
  //counter-clockwise order so that the inside of the planes are the inside
  //of the frustum
  planes[NEAR] = {nearTopLeft, nearTopRight, nearBotRight};
  planes[FAR] = {farTopLeft, farBotLeft, farBotRight};
  planes[TOP] = {farTopRight, nearTopRight, nearTopLeft};
  planes[RIGHT] = {nearTopRight, farTopRight, farBotRight};
  planes[BOTTOM] = {farBotLeft, nearBotLeft, nearBotRight};
  planes[LEFT] = {farTopLeft, nearTopLeft, nearBotLeft};
}

void Graphics3D::Frustum::setFOV(double newFov) {
  set(newFov, aspect, near, far);
}

void Graphics3D::Frustum::setAspect(double newAspect) {
  set(fov, newAspect, near, far);
}

void Graphics3D::Frustum::setNear(double newNear) {
  set(fov, aspect, newNear, far);
}

void Graphics3D::Frustum::setFar(double newFar) {
  set(fov, aspect, near, newFar);
}

double Graphics3D::Frustum::getFOV() const {
  return fov;
}

double Graphics3D::Frustum::getAspect() const {
  return aspect;
}

double Graphics3D::Frustum::getNear() const {
  return near;
}

double Graphics3D::Frustum::getFar() const {
  return far;
}
