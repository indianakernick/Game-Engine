//
//  camera.hpp
//  Game Engine
//
//  Created by Indi Kernick on 13/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_scene_camera_hpp
#define engine_3d_scene_camera_hpp

#include "node.hpp"
#include "../frustum.hpp"

namespace Scene {
  class Camera final : public Node {
  public:
    using Ptr = std::shared_ptr<Camera>;
    
    Camera(Game::Actor::ID, const glm::mat4 &);
    Camera(Game::Actor::ID, const glm::mat4 &, const Graphics3D::Frustum &);
    ~Camera() = default;
    
    Graphics3D::Frustum &getFrustum();
    const Graphics3D::Frustum &getFrustum() const;
    
    const glm::mat4 &getProj() const;
    const glm::mat4 &getView() const;
  private:
    Graphics3D::Frustum frustum;
  };
}

#endif
