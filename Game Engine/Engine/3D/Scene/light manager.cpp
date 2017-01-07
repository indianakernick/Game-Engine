//
//  light manager.cpp
//  Game Engine
//
//  Created by Indi Kernick on 19/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "light manager.hpp"

#include "light node.hpp"

Graphics3D::LightManager::LightManager() {
  lightProps.reserve(MAX_LIGHTS);
}

void Graphics3D::LightManager::calcLighting() {
  assert(lights.size() <= MAX_LIGHTS);
  
  size_t count = 0;
  for (auto i = lights.begin(); i != lights.end(); ++i, ++count) {
    lightProps[count] = (*i)->getLightProp();
  }
}

void Graphics3D::LightManager::calcLighting(Scene *, Program3D *program, SceneNode::Ptr) {
  program->setLights(lightProps);
}

void Graphics3D::LightManager::addLight(std::shared_ptr<LightNode> light) {
  lights.push_back(light);
}

void Graphics3D::LightManager::remLight(std::shared_ptr<LightNode> light) {
  size_t preSize = lights.size();
  lights.remove(light);
  if (preSize == lights.size()) {
    Log::write(Log::SCENE_GRAPH, Log::WARNING, "Tried to remove a light from manager but it was not removed");
  }
}
