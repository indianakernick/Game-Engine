//
//  light node.cpp
//  Game Engine
//
//  Created by Indi Kernick on 19/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "light node.hpp"

Graphics3D::LightNode::LightNode(Game::Actor::ID actor,
                                 const Color3F &color,
                                 float intensity,
                                 const glm::mat4 &toWorld)
 : SceneNode(actor, PASS_INVISIBLE, toWorld, 0.0f) {
  lightProps.color = *reinterpret_cast<const glm::vec3 *>(&color);
  lightProps.intensity = intensity;
  lightProps.pos = toWorld[3];
}

const Graphics3D::LightProperties &Graphics3D::LightNode::getLightProp() {
  lightProps.pos = getProp().getToWorld()[3];
  return lightProps;
}
