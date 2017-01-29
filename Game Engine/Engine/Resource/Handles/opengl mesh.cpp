//
//  opengl mesh.cpp
//  Game Engine
//
//  Created by Indi Kernick on 2/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "opengl mesh.hpp"

#ifdef USE_OPENGL

using namespace Res;

MeshOpenGL::MeshOpenGL(GroupID numGroups,
                       MaterialID numMaterials,
                       const std::vector<bool> &hasUVs,
                       const std::vector<MaterialID> &matIndicies)
  : verts(numGroups),
    norms(numGroups),
    UVs(numGroups, 0),
    hasUVs(hasUVs),
    elems(numGroups),
    matIndicies(matIndicies),
    materials(numMaterials),
    indiciesNum(numGroups),
    boneIDs(numGroups, 0),
    boneWeights(numGroups, 0) {
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

MeshOpenGL::~MeshOpenGL() {
  glDeleteBuffers(static_cast<GLsizei>(verts.size()), verts.data());
  glDeleteBuffers(static_cast<GLsizei>(norms.size()), norms.data());
  glDeleteBuffers(static_cast<GLsizei>(elems.size()), elems.data());
  
  for (size_t i = 0; i < UVs.size(); i++) {
    if (hasUVs[i]) {//not sure about the precedence
      glDeleteBuffers(1, &(UVs[i]));
    }
  }
  
  for (size_t i = 0; i < boneIDs.size(); i++) {
    if (boneIDs[i]) {
      glDeleteBuffers(1, &(boneIDs[i]));
    }
  }
  
  for (size_t i = 0; i < boneWeights.size(); i++) {
    if (boneWeights[i]) {
      glDeleteBuffers(1, &(boneWeights[i]));
    }
  }
}

const std::vector<GLuint> &MeshOpenGL::getVerts() const {
  return verts;
}

const std::vector<GLuint> &MeshOpenGL::getNorms() const {
  return norms;
}

const std::vector<GLuint> &MeshOpenGL::getUVs() const {
  return UVs;
}

const std::vector<bool> &MeshOpenGL::getHasUVs() const {
  return hasUVs;
}

const std::vector<GLuint> &MeshOpenGL::getElems() const {
  return elems;
}

const std::vector<MeshOpenGL::MaterialID> &MeshOpenGL::getMatIndicies() const {
  return matIndicies;;
}

const std::vector<Graphics3D::Material> &MeshOpenGL::getMaterials() const {
  return materials;
}

const std::vector<unsigned> &MeshOpenGL::getIndiciesNum() const {
  return indiciesNum;
}

const std::vector<GLuint> &MeshOpenGL::getBoneIDs() const {
  return boneIDs;
}

const std::vector<GLuint> &MeshOpenGL::getBoneWeights() const {
  return boneWeights;
}

const MeshOpenGL::Anims &MeshOpenGL::getAnimations() const {
  return animations;
}

const MeshOpenGL::AnimNames &MeshOpenGL::getAnimNames() const {
  return animNames;
}

const MeshOpenGL::ChannelNames &MeshOpenGL::getChannelNames() const {
  return channelNames;
}

const MeshOpenGL::Bones &MeshOpenGL::getBones() const {
  return bones;
}

const MeshOpenGL::BoneNodes &MeshOpenGL::getBoneNodes() const {
  return boneNodes;
}

bool MeshOpenGL::hasAnimations() const {
  return animations.size() && bones.size() && boneNodes.size();
}

#endif
