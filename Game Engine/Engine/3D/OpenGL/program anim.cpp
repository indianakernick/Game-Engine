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
  numBones = getUniform("numBones");
  
  boneID = getAttr("boneID");
  boneWeight = getAttr("boneWeight");
}

void Graphics3D::GLProgs::Anim::enableAll() {
  Phong::enableAll();
  glEnableVertexAttribArray(boneID);
  glEnableVertexAttribArray(boneWeight);
}

void Graphics3D::GLProgs::Anim::disableAll() {
  Phong::disableAll();
  glDisableVertexAttribArray(boneID);
  glDisableVertexAttribArray(boneWeight);
}

void Graphics3D::GLProgs::Anim::boneIDPointer(size_t stride, size_t offset) {
  attribPointer<GLuint[MAX_BONES_PER_VERTEX]>(boneID, stride, offset);
}

void Graphics3D::GLProgs::Anim::boneWeightPointer(size_t stride, size_t offset) {
  attribPointer<GLfloat[MAX_BONES_PER_VERTEX]>(boneWeight, stride, offset);
}

void Graphics3D::GLProgs::Anim::setBones(const std::vector<glm::mat4> &bonesData) {
  assert(bonesData.size() <= MAX_BONES);
  
  glUniformMatrix4fv(
    bones,
    static_cast<GLsizei>(bonesData.size()),
    GL_FALSE,
    reinterpret_cast<const GLfloat *>(bonesData.data())
  );
  glUniform1ui(numBones, static_cast<GLsizei>(bonesData.size()));
}

#endif
