//
//  light manager.cpp
//  Game Engine
//
//  Created by Indi Kernick on 19/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "light manager.hpp"

size_t Graphics3D::LightManager::getLightCount(SceneNode::Ptr) const {
  return lights.size();
}

const Color4F *Graphics3D::LightManager::getDiffuse(SceneNode::Ptr) const {
  return diffuse;
}

const glm::vec4 *Graphics3D::LightManager::getDir(SceneNode::Ptr) const {
  return dir;
}

void Graphics3D::LightManager::calcLighting(Scene *) {
  assert(lights.size() <= MAX_LIGHTS);
  size_t count = 0;
  for (auto i = lights.begin(); i != lights.end(); ++i, ++count) {
    diffuse[count] = (*i)->getLightProp().diffuse;
    glm::vec3 lightDir = (*i)->getDir();
    dir[count] = {lightDir.x, lightDir.y, lightDir.z, 1.0f};
  }
}

void Graphics3D::LightManager::calcLighting(SceneNode::Ptr node,
                                            Memory::Buffer buffer,
                                            size_t &lightsCount) {
  lightsCount = getLightCount(node);
  memcpy(buffer.begin(), getDiffuse(node), lightsCount * sizeof(Color4F));
  memcpy(buffer.add(lightsCount * sizeof(Color4F)), getDir(node), lightsCount * sizeof(glm::vec4));
}
