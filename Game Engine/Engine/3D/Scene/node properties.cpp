//
//  node properties.cpp
//  Game Engine
//
//  Created by Indi Kernick on 18/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "node properties.hpp"

Graphics3D::NodeProperties::NodeProperties(Game::Actor::ID actor,
                                           RenderPass pass,
                                           const Material &material,
                                           const glm::mat4 &toWorld,
                                           float radius)
 : actor(actor),
   pass(pass),
   material(material),
   toWorld(toWorld),
   fromWorld(glm::inverse(toWorld)),
   radius(radius) {}

Game::Actor::ID Graphics3D::NodeProperties::getActor() const {
  return actor;
}

Graphics3D::RenderPass Graphics3D::NodeProperties::getPass() const {
  return pass;
}

const Graphics3D::Material &Graphics3D::NodeProperties::getMaterial() const {
  return material;
}

const glm::mat4 &Graphics3D::NodeProperties::getToWorld() const {
  return toWorld;
}

const glm::mat4 &Graphics3D::NodeProperties::getFromWorld() const {
  return fromWorld;
}

float Graphics3D::NodeProperties::getRadius() const {
  return radius;
}
