//
//  node properties.hpp
//  Game Engine
//
//  Created by Indi Kernick on 18/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_scene_node_properties_hpp
#define engine_3d_scene_node_properties_hpp

#include <glm/glm.hpp>
#include "../material.hpp"
#include "../../Game Logic/actor.hpp"

namespace Graphics3D {
  enum RenderPass {
    PASS_FIRST = 0,
    
    PASS_STATIC = PASS_FIRST,
    PASS_DYNAMIC,
    PASS_SKY,
    PASS_INVISIBLE,
    
    PASS_LAST
  };
  
  class NodeProperties {
  friend class SceneNode;
  public:
    NodeProperties() = default;
    NodeProperties(Game::Actor::ID, RenderPass, const glm::mat4 &, float);
  
    Game::Actor::ID getActor() const;
    RenderPass getPass() const;
    const glm::mat4 &getToWorld() const;
    const glm::mat4 &getFromWorld() const;
    float getRadius() const;
  private:
    Game::Actor::ID actor = 0;
    RenderPass pass = PASS_INVISIBLE;
    glm::mat4 toWorld;
    glm::mat4 fromWorld;
    float radius = 0.0f;
  };
}

#endif
