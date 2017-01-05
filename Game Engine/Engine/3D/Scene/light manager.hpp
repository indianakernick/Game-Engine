//
//  light manager.hpp
//  Game Engine
//
//  Created by Indi Kernick on 19/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_scene_light_manager_hpp
#define engine_3d_scene_light_manager_hpp

#include "light node.hpp"
#include <list>
#include "../../Memory/buffer.hpp"

namespace Graphics3D {
  class LightNode;

  class LightManager {
  public:
    using Lights = std::list<std::shared_ptr<LightNode>>;
    static const size_t MAX_LIGHTS = 8;
  
    LightManager() = default;
    
    ///Get the number of lights affecting the node
    size_t getLightCount(SceneNode::Ptr) const;
    ///Get the diffuse of the lights affecting the node
    const Color4F *getDiffuse(SceneNode::Ptr) const;
    ///Get the direction of the lights affecting the node
    const glm::vec4 *getDir(SceneNode::Ptr) const;
    ///Get information from the LightNodes
    void calcLighting(Scene *scene);
    ///Pack the lighting information affecting a SceneNode into a
    ///buffer to be sent to the shaders
    void calcLighting(SceneNode::Ptr, Memory::Buffer, size_t &);
    
  private:
    Lights lights;
    Color4F diffuse[MAX_LIGHTS];
    glm::vec4 dir[MAX_LIGHTS];
  };
}

#endif
