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
                       const std::vector<MaterialID> &matIndicies)
  : VAOs(numGroups),
    matIndicies(matIndicies),
    materials(numMaterials),
    indiciesNum(numGroups) {
  assert(matIndicies.size() == numGroups);
  this->matIndicies.shrink_to_fit();
  glGenVertexArrays(numGroups, VAOs.data());
}

MeshOpenGL::~MeshOpenGL() {
  glDeleteVertexArrays(static_cast<GLsizei>(VAOs.size()), VAOs.data());
  glDeleteBuffers(static_cast<GLsizei>(buffers.size()), buffers.data());
}

const std::vector<GLuint> &MeshOpenGL::getVAOs() const {
  return VAOs;
}

const std::vector<MeshOpenGL::MaterialID> &MeshOpenGL::getMatIndicies() const {
  return matIndicies;
}

const std::vector<Graphics3D::Material> &MeshOpenGL::getMaterials() const {
  return materials;
}

const std::vector<unsigned> &MeshOpenGL::getIndiciesNum() const {
  return indiciesNum;
}

const std::vector<Graphics3D::ProgType> &MeshOpenGL::getProgTypes() const {
  return progTypes;
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
