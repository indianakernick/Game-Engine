//
//  program anim.cpp
//  Game Engine
//
//  Created by Indi Kernick on 24/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "program anim.hpp"

#ifdef USE_OPENGL

Graphics3D::GLProgs::Anim::Anim(const char *name)
  : Phong(name, "anim texture.vert", "phong texture.frag") {}

void Graphics3D::GLProgs::Anim::load() {
  Phong::load();
  
  bones = getUniform("bones");
  
  boneID = getAttr("boneID");
  boneWeight = getAttr("boneWeight");
}

void Graphics3D::GLProgs::Anim::enableAll() {
  Phong::enableAll();
  enableBones();
}

void Graphics3D::GLProgs::Anim::disableAll() {
  Phong::disableAll();
  disableBones();
}

void Graphics3D::GLProgs::Anim::enableBones() {
  enableArray(boneID, MAX_BONES_PER_VERTEX);
  enableArray(boneWeight, MAX_BONES_PER_VERTEX);
}

void Graphics3D::GLProgs::Anim::disableBones() {
  disableArray(boneID, MAX_BONES_PER_VERTEX);
  disableArray(boneWeight, MAX_BONES_PER_VERTEX);
}

void Graphics3D::GLProgs::Anim::boneIDPointer() {
  attribPointerArray<GLuint>(boneID, MAX_BONES_PER_VERTEX, 0, 0);
}

void Graphics3D::GLProgs::Anim::boneWeightPointer() {
  attribPointerArray<GLfloat>(boneWeight, MAX_BONES_PER_VERTEX, 0, 0);
}

void Graphics3D::GLProgs::Anim::setBones(const std::vector<glm::mat4> &bonesData) {
  assert(bonesData.size() <= MAX_BONES);
  setUniformArray(bones, bonesData);
}

#endif
