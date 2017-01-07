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
#include "../../Utils/logger.hpp"
#include "../matstack.hpp"

namespace Graphics3D {
  class Scene;
  class CameraNode;
  class Program3D;

  class SceneNode {
  public:
    using Ptr = std::shared_ptr<SceneNode>;
  
    SceneNode(Game::Actor::ID, RenderPass, const glm::mat4 &, float);
    virtual ~SceneNode() = default;
    
    const NodeProperties &getProp() const;
    
    virtual void setTransform(const glm::mat4 &toWorld, const glm::mat4 &fromWorld);
    //calculates fromWorld
    virtual void setToWorld(const glm::mat4 &toWorld);
    //calculates toWorld
    virtual void setFromWorld(const glm::mat4 &fromWorld);
    
    virtual void restore(Scene *scene);
    virtual void update(Scene *scene, uint64_t delta);
    virtual bool isVisible(std::shared_ptr<CameraNode>) const;
    
    virtual void preRender(MatStack &);
    virtual void render(MatStack &, Program3D *, std::shared_ptr<CameraNode>);
    virtual void renderChildren(MatStack &, Program3D *, std::shared_ptr<CameraNode>);
    virtual void postRender(MatStack &);
    
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

#endif
