//
//  scene node.hpp
//  Game Engine
//
//  Created by Indi Kernick on 18/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_scene_scene_node_hpp
#define engine_3d_scene_scene_node_hpp

#include "node properties.hpp"
#include <memory>
#include <vector>
#include <glm/gtx/matrix_decompose.hpp>

namespace Graphics3D {
  class Scene;

  class SceneNode {
  public:
    using Ptr = std::shared_ptr<SceneNode>;
  
    SceneNode(Game::Actor::ID, RenderPass, const glm::mat4 &, float);
    virtual ~SceneNode() = default;
    
    const NodeProperties &getProp() const;
    
    void setTransform(const glm::mat4 &toWorld, const glm::mat4 &fromWorld);
    //calculates fromWorld
    void setToWorld(const glm::mat4 &toWorld);
    //calculates toWorld
    void setFromWorld(const glm::mat4 &fromWorld);
    
    virtual void restore(Scene *scene);
    virtual void update(Scene *scene, uint64_t delta);
    virtual bool isVisible(Scene *scene) const;
    
    virtual void preRender(Scene *scene);
    virtual void render(Scene *) {};
    virtual void renderChildren(Scene *scene);
    virtual void postRender(Scene *scene);
    
    virtual void addChild(SceneNode::Ptr);
    virtual void remChild(Game::Actor::ID);
    virtual void remSelf() const;
    ///Remove a child without destroying it
    virtual SceneNode::Ptr detachChild(Game::Actor::ID);
    
    //for debug (i was almost going to call this countDeadChildren but that
    //seemed a little grusome!)
    size_t countNullChildren() const;
    
  protected:
    NodeProperties prop;
    std::vector<SceneNode::Ptr> children;
    SceneNode *parent = nullptr;
  };
}

#include "scene.hpp"

#endif
