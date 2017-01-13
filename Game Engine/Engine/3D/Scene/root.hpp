//
//  root.hpp
//  Game Engine
//
//  Created by Indi Kernick on 13/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_scene_root_hpp
#define engine_3d_scene_root_hpp

#include "node.hpp"
#include <unordered_map>
#include "../../Utils/logger.hpp"

namespace Scene {
  class Root {
  public:
    using Ptr = std::shared_ptr<Root>;
    
    Root();
    ~Root() = default;
    
    void restore() const;
    void update(uint64_t) const;
    
    bool hasChildren() const;
    size_t numChildren() const;
    const Node::Children &getChildren() const;
    
    Node::Ptr getNode(Game::Actor::ID) const;
    void addChildTo(Game::Actor::ID, Node::Ptr);
    void addChild(Node::Ptr);
    void remChild(Game::Actor::ID);
    Node::Ptr detachChild(Game::Actor::ID);
    
    void setActiveCamera(Game::Actor::ID);
    Node::Ptr getActiveCamera() const;
    
  private:
    Node::Ptr node;
    Node::Ptr activeCamera = nullptr;
    std::unordered_map<Game::Actor::ID, Node::Ptr> nodeMap;
  };
}

#endif
