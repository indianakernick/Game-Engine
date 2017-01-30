//
//  program anim.cpp
//  Game Engine
//
//  Created by Indi Kernick on 24/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "program anim.hpp"

#ifdef USE_OPENGL

Graphics3D::AnimPhong::AnimPhong(const char *name)
  : Phong(name, "anim phong texture.vert", "phong texture.frag") {}

void Graphics3D::AnimPhong::load() {
  Phong::load();
  
  bones = getUniform("bones");
}

void Graphics3D::AnimPhong::enableAll() {
  Phong::enableAll();
  enableBones();
}

void Graphics3D::AnimPhong::disableAll() {
  Phong::disableAll();
  disableBones();
}

void Graphics3D::AnimPhong::enableBones() {
  enableBoneID();
  enableBoneWeight();
}

void Graphics3D::AnimPhong::disableBones() {
  disableBoneID();
  disableBoneWeight();
}

void Graphics3D::AnimPhong::setBones(const std::vector<glm::mat4> &bonesData) {
  assert(bonesData.size() <= MAX_BONES);
  setUniformArray(bones, bonesData);
}

#endif
