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
  : Phong(name, "anim phong texture.vert", "phong texture.frag") {}

void Graphics3D::GLProgs::Anim::load() {
  Phong::load();
  
  bones = getUniform("bones");
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
  enableArray<BONE_ID_LOC, MAX_BONES_PER_VERTEX>();
  enableArray<BONE_WGHT_LOC, MAX_BONES_PER_VERTEX>();
}

void Graphics3D::GLProgs::Anim::disableBones() {
  disableArray<BONE_ID_LOC, MAX_BONES_PER_VERTEX>();
  disableArray<BONE_WGHT_LOC, MAX_BONES_PER_VERTEX>();
}

void Graphics3D::GLProgs::Anim::boneIDPointer(size_t stride, size_t offset) {
  attribPointerArray<GLuint, BONE_ID_LOC, MAX_BONES_PER_VERTEX>(stride, offset);
}

void Graphics3D::GLProgs::Anim::boneWeightPointer(size_t stride, size_t offset) {
  attribPointerArray<GLfloat, BONE_WGHT_LOC, MAX_BONES_PER_VERTEX>(stride, offset);
}

void Graphics3D::GLProgs::Anim::setBones(const std::vector<glm::mat4> &bonesData) {
  assert(bonesData.size() <= MAX_BONES);
  setUniformArray(bones, bonesData);
}

#endif
