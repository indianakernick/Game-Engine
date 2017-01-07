//
//  scene.cpp
//  Game Engine
//
//  Created by Indi Kernick on 18/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "scene node.hpp"
#include "root node.hpp"
#include "camera node.hpp"
#include "light manager.hpp"
#include "light node.hpp"

#include "scene.hpp"

//i would normally put all the #includes in the header but this is the only way
//i could get this thing to compile. I had to make some sacrifics and remove
//functionality just to get it to compile

//it seems like everything depends on everything so i need to redesign this so
//that its more flexible

Graphics3D::Scene::Scene()
  : root(std::make_shared<RootNode>()),
    camera(std::make_shared<CameraNode>(glm::mat4(), Frustum())),
    lightManager(std::make_shared<LightManager>()),
    program3d(makeProgram3D()) {
  program3d->load();
}

void Graphics3D::Scene::restore() {
  root->restore(this);
}

void Graphics3D::Scene::update(uint64_t delta) {
  root->update(this, delta);
}

void Graphics3D::Scene::render() {
  camera->setViewTransform(this);
  lightManager->calcLighting();
  
  root->preRender(matStack);
  root->render(matStack, program3d.get(), camera);
  root->renderChildren(matStack, program3d.get(), camera);
  root->postRender(matStack);
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
    std::shared_ptr<LightNode> light = std::dynamic_pointer_cast<LightNode>(child);
    if (light) {
      lightManager->addLight(light);
    }
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
    std::shared_ptr<LightNode> light = std::dynamic_pointer_cast<LightNode>(iter->second);
    if (light) {
      lightManager->remLight(light);
    }
    iter->second->remSelf();
  } else {
    throw std::runtime_error("Failed to remove node: node was not found");
  }
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

Graphics3D::Program3D::Ptr Graphics3D::Scene::getProgram3d() const {
  return program3d;
}
