//
//  light manager.hpp
//  Game Engine
//
//  Created by Indi Kernick on 19/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_scene_light_manager_hpp
#define engine_3d_scene_light_manager_hpp

#include <list>
#include "../../Utils/logger.hpp"
#include "../light properties.hpp"
#include <vector>
#include "../program 3d.hpp"

namespace Graphics3D {
  class LightNode;
  class Scene;
  class SceneNode;

  class LightManager {
  public:
    static const size_t MAX_LIGHTS = 8;
  
    LightManager();
    
    ///Get information from the LightNodes
    void calcLighting();
    ///Send the lighting information affecting a SceneNode to the shader
    void calcLighting(Scene *, Program3D *, std::shared_ptr<SceneNode>);
    
    void addLight(std::shared_ptr<LightNode>);
    void remLight(std::shared_ptr<LightNode>);
    
  private:
    std::list<std::shared_ptr<LightNode>> lights;
    std::vector<LightProperties> lightProps;
  };
}

#endif
