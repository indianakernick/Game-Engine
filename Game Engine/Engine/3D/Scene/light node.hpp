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
#include "../color.hpp"
#include "../light properties.hpp"

namespace Graphics3D {
  class LightNode : public SceneNode {
  public:
    using Ptr = std::shared_ptr<LightNode>;
  
    LightNode(Game::Actor::ID, const Color3F &color, float intensity, const glm::mat4 &);
    
    const LightProperties &getLightProp();
    
  protected:
    LightProperties lightProps;
  };
};

#endif
