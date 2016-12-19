//
//  light node.cpp
//  Game Engine
//
//  Created by Indi Kernick on 19/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "light node.hpp"

Graphics3D::LightNode::LightNode(Game::Actor::ID actor,
                                 const LightProperties &props,
                                 const Material &material,
                                 const glm::mat4 &toWorld)
 : SceneNode(actor, PASS_INVISIBLE, material, toWorld, 0.0f),
   lightProps(props) {}

glm::vec3 &Graphics3D::LightNode::getDir() {
  return lightProps.dir;
}

Graphics3D::LightProperties &Graphics3D::LightNode::getLightProp() {
  return lightProps;
}
