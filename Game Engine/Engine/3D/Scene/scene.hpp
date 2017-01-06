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
#include <memory>
#include "../../Game Logic/actor.hpp"

namespace Graphics3D {
  class RootNode;
  class CameraNode;
  class LightManager;
  class SceneNode;

  class Scene {
  public:
    using Ptr = std::shared_ptr<Scene>;
  
    Scene();
    virtual ~Scene() = default;
    
    void restore();
    void update(uint64_t delta);
    void render();
  
    std::shared_ptr<SceneNode> getNode(Game::Actor::ID) const;
    void addChild(Game::Actor::ID, std::shared_ptr<SceneNode>);
    void addRootChild(std::shared_ptr<SceneNode>);
    void remChild(Game::Actor::ID);
  
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
    std::shared_ptr<LightManager> lightManager;
    
    std::map<Game::Actor::ID, std::shared_ptr<SceneNode>> actorMap;
  };
}

#include "root node.hpp"
#include "camera node.hpp"
#include "light manager.hpp"

#endif
