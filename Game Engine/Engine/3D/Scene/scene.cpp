//
//  scene.cpp
//  Game Engine
//
//  Created by Indi Kernick on 18/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "scene.hpp"

Graphics3D::Scene::Scene()
  : root(std::make_shared<RootNode>()),
    camera(std::make_shared<CameraNode>(glm::mat4(), Frustum())),
    lightManager(std::make_shared<LightManager>()) {}

void Graphics3D::Scene::restore() {
  root->restore(this);
}

void Graphics3D::Scene::update(uint64_t delta) {
  root->update(this, delta);
}

void Graphics3D::Scene::render() {
  camera->setViewTransform(this);
  lightManager->calcLighting(this);
  
  root->preRender(this);
  root->render(this);
  root->renderChildren(this);
  root->postRender(this);
}

Graphics3D::SceneNode::Ptr Graphics3D::Scene::getNode(Game::Actor::ID actor) const {
  auto iter = actorMap.find(actor);
  if (iter != actorMap.end()) {
    return iter->second;
  } else {
    return nullptr;
  }
}

void Graphics3D::Scene::addChild(Game::Actor::ID parent, SceneNode::Ptr child) {
  auto iter = actorMap.find(parent);
  if (iter != actorMap.end()) {
    iter->second->addChild(child);
  } else {
    throw std::runtime_error("Failed to add child: the parent was not found");
  }
}

void Graphics3D::Scene::addRootChild(SceneNode::Ptr child) {
  root->addChild(child);
}

void Graphics3D::Scene::remChild(Game::Actor::ID child) {
  auto iter = actorMap.find(child);
  if (iter != actorMap.end()) {
    iter->second->remSelf();
  } else {
    throw std::runtime_error("Failed to remove node: node was not found");
  }
}

void Graphics3D::Scene::pushMat(const glm::mat4 &mat) {
  matStack.push(mat);
}

void Graphics3D::Scene::popMat() {
  matStack.pop();
}

const glm::mat4 &Graphics3D::Scene::topMat() const {
  return matStack.top();
}

void Graphics3D::Scene::setCamera(Graphics3D::CameraNode::Ptr newCamera) {
  camera = newCamera;
}

Graphics3D::CameraNode::Ptr Graphics3D::Scene::getCamera() const {
  return camera;
}

Graphics3D::LightManager &Graphics3D::Scene::getLightManager() {
  return *lightManager;
}

Graphics3D::RootNode::Ptr Graphics3D::Scene::getRoot() const {
  return root;
}
