//
//  scene.hpp
//  Game Engine
//
//  Created by Indi Kernick on 18/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_scene_scene_hpp
#define engine_3d_scene_scene_hpp

#include "../matstack.hpp"
#include <list>
#include <map>
#include "root node.hpp"
#include "camera node.hpp"
#include "../../Application/renderer.hpp"
#include <memory>
#include "light manager.hpp"

namespace Graphics3D {
  class RootNode;
  class CameraNode;
  class LightManager;

  class Scene {
  public:
    Scene();
    virtual ~Scene() = default;
    
    void restore();
    void update(uint64_t delta);
    void render();
  
    SceneNode::Ptr getNode(Game::Actor::ID) const;
  
    void pushMat(const glm::mat4 &);
    void popMat();
    const glm::mat4 &topMat() const;
    
    void setCamera(std::shared_ptr<CameraNode>);
    std::shared_ptr<CameraNode> getCamera() const;
    
    LightManager &getLightManager();
    std::shared_ptr<RootNode> getRoot() const;
  protected:
    MatStack matStack;
    
    std::shared_ptr<RootNode> root;
    std::shared_ptr<CameraNode> camera;
    Renderer::Ptr renderer;
    std::shared_ptr<LightManager> lightManager;
    
    std::map<Game::Actor::ID, SceneNode::Ptr> actorMap;
  };
}

#endif
