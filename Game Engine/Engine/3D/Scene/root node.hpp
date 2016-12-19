//
//  root node.hpp
//  Game Engine
//
//  Created by Indi Kernick on 19/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_scene_root_node_hpp
#define engine_3d_scene_root_node_hpp

#include "scene node.hpp"

namespace Graphics3D {
  class RootNode : public SceneNode {
  public:
    using Ptr = std::shared_ptr<RootNode>;
    
    RootNode();
    virtual ~RootNode() = default;
    
    bool isVisible(Scene *) const override;
    void renderChildren(Scene *) override;
    void addChild(SceneNode::Ptr) override;
  };
}

#endif
