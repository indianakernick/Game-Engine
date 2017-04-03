//
//  mesh.hpp
//  Game Engine
//
//  Created by Indi Kernick on 13/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_scene_mesh_hpp
#define engine_3d_scene_mesh_hpp

#include "node.hpp"
#include "../../Resource/id.hpp"

namespace Scene {
  class Mesh final : public Node {
  public:
    using Ptr = std::shared_ptr<Mesh>;
  
    Mesh(Game::Actor::ID, const glm::mat4 &, const Res::ID &);
    
    const Res::ID &getMesh() const;
  private:
    Res::ID mesh;
  };
}

#endif
