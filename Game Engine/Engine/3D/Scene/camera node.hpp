//
//  camera node.hpp
//  Game Engine
//
//  Created by Indi Kernick on 19/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_scene_camera_node_hpp
#define engine_3d_scene_camera_node_hpp

#include "scene node.hpp"
#include "frustum.hpp"
#include "../../Application/base.hpp"

namespace Graphics3D {
  class CameraNode : public SceneNode {
  public:
    using Ptr = std::shared_ptr<CameraNode>;
    
    CameraNode(const glm::mat4 &, const Frustum &);
    
    void restore(Scene *) override;
    
    void setViewTransform(Scene *);
    
    const Frustum &getFrustum() const;
    const glm::mat4 &getView() const;
    const glm::mat4 &getProj() const;
    glm::mat4 getViewProj() const;
    
  private:
    Frustum frustum;
    //traverses up the scene graph to calculate to toWorld matrix
    //before the graph is traversed properly
    glm::mat4 getTransform();
  };
}

#endif
