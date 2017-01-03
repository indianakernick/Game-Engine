//
//  opengl mesh.cpp
//  Game Engine
//
//  Created by Indi Kernick on 2/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "opengl mesh.hpp"

Resource::Descs::MeshOpenGL::MeshOpenGL(uint8_t numMaterials,
                                        uint8_t numGroups,
                                        const std::vector<bool> &hasUVs,
                                        const std::vector<uint8_t> &matIndicies)
  : verts(numGroups),
    norms(numGroups),
    UVs(numGroups, 0),
    hasUVs(hasUVs),
    elems(numGroups),
    matIndicies(matIndicies),
    materials(numMaterials) {
  verts.shrink_to_fit();
  norms.shrink_to_fit();
  UVs.shrink_to_fit();
  assert(hasUVs.size() == numGroups);
  this->hasUVs.shrink_to_fit();
  elems.shrink_to_fit();
  assert(matIndicies.size() == numGroups);
  this->matIndicies.shrink_to_fit();
  
  glGenBuffers(static_cast<GLsizei>(numGroups), verts.data());
  glGenBuffers(static_cast<GLsizei>(numGroups), norms.data());
  glGenBuffers(static_cast<GLsizei>(numGroups), elems.data());
  
  for (size_t i = 0; i < numGroups; i++) {
    if (hasUVs[i]) {
      glGenBuffers(1, &(UVs[i]));
    }
  }
}

Resource::Descs::MeshOpenGL::~MeshOpenGL() {
  glDeleteBuffers(static_cast<GLsizei>(verts.size()), verts.data());
  glDeleteBuffers(static_cast<GLsizei>(norms.size()), norms.data());
  glDeleteBuffers(static_cast<GLsizei>(elems.size()), elems.data());
  
  for (size_t i = 0; i < UVs.size(); i++) {
    if (hasUVs[i]) {//not sure about the precedence
      glDeleteBuffers(1, &(UVs[i]));
    }
  }
}

const std::vector<GLuint> &Resource::Descs::MeshOpenGL::getVerts() const {
  return verts;
}

const std::vector<GLuint> &Resource::Descs::MeshOpenGL::getNorms() const {
  return norms;
}

const std::vector<GLuint> &Resource::Descs::MeshOpenGL::getUVs() const {
  return UVs;
}

const std::vector<bool> &Resource::Descs::MeshOpenGL::getHasUVs() const {
  return hasUVs;
}

const std::vector<GLuint> &Resource::Descs::MeshOpenGL::getElems() const {
  return elems;
}

const std::vector<uint8_t> &Resource::Descs::MeshOpenGL::getMatIndicies() const {
  return matIndicies;;
}

Resource::Descs::MeshOpenGL::Material &Resource::Descs::MeshOpenGL::getMaterial(uint8_t i) {
  assert(i < materials.size());
  return materials[i];
}