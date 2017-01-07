//
//  opengl mesh node.hpp
//  Game Engine
//
//  Created by Indi Kernick on 29/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_scene_opengl_mesh_node_hpp
#define engine_3d_scene_opengl_mesh_node_hpp

#ifdef USE_OPENGL

#include "../../Application/opengl.hpp"
#include "scene node.hpp"
#include "../../Resource/Descriptions/opengl mesh.hpp"
#include "../OpenGL/program 3d.hpp"
#include "../../Application/base.hpp"

namespace Graphics3D {
  class MatStack;
  class CameraNode;

  class MeshNode : public SceneNode {
  public:
    MeshNode(Game::Actor::ID, Resource::ID, RenderPass, const glm::mat4 &);
    
    void render(MatStack &, Program3D *, std::shared_ptr<CameraNode>) override;
  private:
    Resource::ID mesh;
  };
}

#endif

#endif
