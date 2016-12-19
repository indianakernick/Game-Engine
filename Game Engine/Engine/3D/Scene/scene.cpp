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
    renderer(app->renderer),
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
  
  renderAlpha();
}

Graphics3D::SceneNode::Ptr Graphics3D::Scene::getNode(Game::Actor::ID actor) const {
  auto iter = actorMap.find(actor);
  if (iter != actorMap.end()) {
    return iter->second;
  } else {
    return nullptr;
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

void Graphics3D::Scene::pushAlphaNode(const AlphaSceneNode &alphaNode) {
  alphaNodes.push_back(alphaNode);
}

Graphics3D::LightManager &Graphics3D::Scene::getLightManager() {
  return *lightManager;
}

Graphics3D::RootNode::Ptr Graphics3D::Scene::getRoot() const {
  return root;
}

void Graphics3D::Scene::renderAlpha() {
  //set up an alpha blend
  
  //in the book there was a class that set up the context for alpha blending
  //when it was constructed and restored the context on destruction
  
  alphaNodes.sort([](const AlphaSceneNode &a, const AlphaSceneNode &b) {
    return a.depth > b.depth;
  });
  while (!alphaNodes.empty()) {
    //the matrix stack should have the identiy matrix
    //on top when this is called
    matStack.push(alphaNodes.front().toWorld);
    alphaNodes.front().node->render(this);
    matStack.pop();
    alphaNodes.pop_front();
  }
}
