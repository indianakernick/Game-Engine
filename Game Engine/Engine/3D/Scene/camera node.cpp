//
//  camera node.cpp
//  Game Engine
//
//  Created by Indi Kernick on 19/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "camera node.hpp"

Graphics3D::CameraNode::CameraNode(const glm::mat4 &toWorld, const Frustum &frustum)
  : SceneNode(Game::Actor::NULL_ID, PASS_FIRST, toWorld, 0.0f),
    frustum(frustum) {}

void Graphics3D::CameraNode::restore(Scene *) {
  frustum.setAspect(app->window->getSize().aspect());
}

void Graphics3D::CameraNode::setViewTransform(Scene *) {
  //send the matricies to the shader
}

const Graphics3D::Frustum &Graphics3D::CameraNode::getFrustum() const {
  return frustum;
}

const glm::mat4 &Graphics3D::CameraNode::getView() const {
  return getProp().getFromWorld();
}

const glm::mat4 &Graphics3D::CameraNode::getProj() const {
  return frustum.getMat();
}

glm::mat4 Graphics3D::CameraNode::getViewProj() const {
  return getProj() * getView();
}
