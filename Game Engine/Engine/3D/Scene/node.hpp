//
//  node.hpp
//  Game Engine
//
//  Created by Indi Kernick on 13/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_scene_node_hpp
#define engine_3d_scene_node_hpp

#include <glm/mat4x4.hpp>
#include <list>
#include <memory>
#include "../../Game Logic/actor.hpp"
#include "../../Utils/logger.hpp"

namespace Scene {
  class Node {
  public:
    using Ptr = std::shared_ptr<Node>;
    using Children = std::list<Node::Ptr>;
  
    Node() = default;
    Node(Game::Actor::ID, const glm::mat4 &);
    virtual ~Node() = default;
    
    virtual void restore();
    virtual void update(uint64_t);
    
    bool hasParent() const;
    Node *getParent() const;
    
    bool hasChildren() const;
    size_t numChildren() const;
    const Children &getChildren() const;
    
    void addChild(Node::Ptr);
    void remChild(Node::Ptr);
    void remChild(Game::Actor::ID);
    void remSelf();
    Node::Ptr detachChild(Game::Actor::ID);
    
    void setToWorld(const glm::mat4 &);
    void setFromWorld(const glm::mat4 &);
    const glm::mat4 &getToWorld() const;
    const glm::mat4 &getFromWorld() const;
    
    Game::Actor::ID getActorID() const;
  protected:
    void restoreChildren() const;
    void updateChildren(uint64_t) const;
  private:
    Node *parent = nullptr;
    Children children;
    
    Game::Actor::ID actor = Game::Actor::NULL_ID;
    glm::mat4 toWorld;
    glm::mat4 fromWorld;
  };
}

#endif
