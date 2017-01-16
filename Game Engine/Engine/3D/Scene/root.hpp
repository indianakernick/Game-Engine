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
#include <list>
#include <map>
#include "../../Utils/logger.hpp"
#include "light.hpp"
#include "camera.hpp"

namespace Scene {
  class Root {
  public:
    using Ptr = std::shared_ptr<Root>;
    using Lights = std::list<std::shared_ptr<Light>>;
    using Nodes = std::map<Game::Actor::ID, Node::Ptr>;
    
    Root();
    ~Root() = default;
    
    void restore() const;
    void update(uint64_t) const;
    
    bool hasChildren() const;
    size_t numChildren() const;
    const Node::Children &getChildren() const;
    
    ///Search for a node in the tree
    Node::Ptr getNode(Game::Actor::ID) const;
    ///Add a node as a child to an existing node
    void addChildTo(Game::Actor::ID, Node::Ptr);
    ///Add a node as a child to the root
    void addChild(Node::Ptr);
    ///Remove a node from the tree, destroying it
    void remChild(Game::Actor::ID);
    ///Detach a node from the tree, without desstroying it
    Node::Ptr detachChild(Game::Actor::ID);
    
    ///Set the active camera to a node in the tree
    void setActiveCamera(Game::Actor::ID);
    Camera::Ptr getActiveCamera() const;
    
    ///Get all lights on the tree
    const Lights &getLights() const;
    ///Get all nodes on the tree (including lights)
    const Nodes &getNodes() const;
  private:
    Node::Ptr node;
    Camera::Ptr activeCamera = nullptr;
    Lights lights;
    Nodes nodes;
  };
}

#endif
