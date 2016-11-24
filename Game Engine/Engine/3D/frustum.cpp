//
//  frustum.cpp
//  Game Engine
//
//  Created by Indi Kernick on 13/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "frustum.hpp"

/*Frustum::Frustum() {
  set(fov, aspect, near, far);
}

Frustum::Frustum(double fov, double aspect, double near, double far) {
  set(fov, aspect, near, far);
}

Mat44 Frustum::getMat() {
  double nearHeightD2 = near * tan(fov / 2);
  double r = nearHeightD2 * aspect,
         l = -r,
         t = nearHeightD2,
         b = -t,
         n = near,
         f = far;
  return {
    {2 * n / (r - l),   0,                 0,                    0},
    {0,                 2 * n / (t - b),   0,                    0},
    {(r + l) / (r - l), (t + b) / (t - b), -(f + n) / (f - n),   -1},
    {0,                 0,                 -2 * f * n / (f - n), 0}
  };
}

bool Frustum::inside(const Vec3 &point) const {
  for (int i = 0; i < 6; i++) {
    if (!planes[i].inside(point)) {
      return false;
    }
  }
  return true;
}

void Frustum::set(double fov, double aspect, double near, double far) {
  assert(fov > 0);
  assert(fov < Math::PI);
  assert(aspect > 0);
  assert(near > 0);
  assert(far > 0);
  assert(far > near);
  
  double tanFovD2 = tan(fov / 2);
  
  double nearHeightD2 = near * tanFovD2;
  double nearWidthD2 = nearHeightD2 * aspect;
  double farHeightD2 = far * tanFovD2;
  double farWidthD2 = farHeightD2 * aspect;
  
  Vec3 nearTopRight(nearWidthD2,nearHeightD2,near);
  Vec3 nearBotRight(nearWidthD2,-nearHeightD2,near);
  Vec3 nearBotLeft(-nearWidthD2,-nearHeightD2,near);
  Vec3 nearTopLeft(-nearWidthD2,nearHeightD2,near);
  
  Vec3 farTopRight(farWidthD2,farHeightD2,far);
  Vec3 farBotRight(farWidthD2,-farHeightD2,far);
  Vec3 farBotLeft(-farWidthD2,-farHeightD2,far);
  Vec3 farTopLeft(-farWidthD2,farHeightD2,far);
  
  //counter-clockwise order so that the inside of the planes are the inside
  //of the frustum
  planes[NEAR] = {nearTopLeft, nearTopRight, nearBotRight};
  planes[FAR] = {farTopLeft, farBotLeft, farBotRight};
  planes[TOP] = {farTopRight, nearTopRight, nearTopLeft};
  planes[RIGHT] = {nearTopRight, farTopRight, farBotRight};
  planes[BOTTOM] = {farBotLeft, nearBotLeft, nearBotRight};
  planes[LEFT] = {farTopLeft, nearTopLeft, nearBotLeft};
}

void Frustum::get(double &fov, double &aspect, double &near, double &far) const {
  fov = this->fov;
  aspect = this->aspect;
  near = this->near;
  far = this->far;
}

void Frustum::setFOV(double newFov) {
  set(newFov, aspect, near, far);
}

void Frustum::setAspect(double newAspect) {
  set(fov, newAspect, near, far);
}

void Frustum::setNear(double newNear) {
  set(fov, aspect, newNear, far);
}

void Frustum::setFar(double newFar) {
  set(fov, aspect, near, newFar);
}

double Frustum::getFOV() const {
  return fov;
}

double Frustum::getAspect() const {
  return aspect;
}

double Frustum::getNear() const {
  return near;
}

double Frustum::getFar() const {
  return far;
}*/
