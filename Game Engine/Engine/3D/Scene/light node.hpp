//
//  light node.hpp
//  Game Engine
//
//  Created by Indi Kernick on 19/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_scene_light_node_hpp
#define engine_3d_scene_light_node_hpp

#include "scene node.hpp"

namespace Graphics3D {
  struct LightProperties {
    Color4F diffuse;
    float attenuation[3];
    float range;
    float falloff;
    float theta;
    float phi;
  };
  
  class LightNode : public SceneNode {
  public:
    using Ptr = std::shared_ptr<LightNode>;
  
    LightNode(Game::Actor::ID, const LightProperties &, const glm::mat4 &);
    
    glm::vec3 getDir();
    LightProperties &getLightProp();
    
  protected:
    LightProperties lightProps;
  };
};

#endif
