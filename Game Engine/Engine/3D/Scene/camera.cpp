//
//  camera.cpp
//  Game Engine
//
//  Created by Indi Kernick on 13/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "camera.hpp"

Scene::Camera::Camera(Game::Actor::ID actor, const glm::mat4 &toWorld)
  : Node(actor, toWorld), frustum() {}

Scene::Camera::Camera(Game::Actor::ID actor,
                      const glm::mat4 &toWorld,
                      const Graphics3D::Frustum &frustum)
  : Node(actor, toWorld), frustum(frustum) {}

Graphics3D::Frustum &Scene::Camera::getFrustum() {
  return frustum;
}

const Graphics3D::Frustum &Scene::Camera::getFrustum() const {
  return frustum;
}

const glm::mat4 &Scene::Camera::getProj() const {
  return frustum.getMat();
}

const glm::mat4 &Scene::Camera::getView() const {
  return getFromWorld();
}
