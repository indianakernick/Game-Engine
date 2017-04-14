//
//  mesh.cpp
//  Game Engine
//
//  Created by Indi Kernick on 14/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "mesh.hpp"

Res::Mesh::Mesh(Platform::Mesh::Ptr mesh)
  : mesh(mesh) {
  assert(mesh);
}

Platform::Mesh::Ptr Res::Mesh::getMesh() const {
  return mesh;
}

const Res::Mesh::Anims &Res::Mesh::getAnims() const {
  return anims;
}

const Res::Mesh::AnimNames &Res::Mesh::getAnimNames() const {
  return animNames;
}

const Res::Mesh::ChannelNames &Res::Mesh::getChannelNames() const {
  return channelNames;
}

const Res::Mesh::Bones &Res::Mesh::getBones() const {
  return bones;
}

const Res::Mesh::BoneNodes &Res::Mesh::getBoneNodes() const {
  return boneNodes;
}
