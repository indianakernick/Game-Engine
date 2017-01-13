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
  class Mesh : public Node {
  public:
    Mesh(Game::Actor::ID, const glm::mat4 &, const Resource::ID &);
    
    const Resource::ID &getMesh() const;
  private:
    Resource::ID mesh;
  };
}

#endif
