//
//  opengl mesh node.cpp
//  Game Engine
//
//  Created by Indi Kernick on 29/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "opengl mesh node.hpp"

#ifdef USE_OPENGL

Graphics3D::MeshNode::MeshNode(Game::Actor::ID actor, Resource::ID mesh,
                               RenderPass pass, const glm::mat4 &toWorld)
  : SceneNode(actor, pass, toWorld, 0.0f),
    mesh(mesh) {}

void Graphics3D::MeshNode::render(Scene *scene) {
  Resource::Handle::Ptr meshHandle = app->cache->get(mesh);
  Resource::Descs::MeshOpenGL::Ptr meshDesc =
    meshHandle->getDesc<Resource::Descs::MeshOpenGL>();
  
  ProgramOpenGL3D *program = dynamic_cast<ProgramOpenGL3D *>(scene->getProgram3d().get());
  //this should never be null because of the USE_OPENGL macro
  assert(program);
  
  meshDesc->createVertexArrays(*program);
  meshDesc->render(*program);
}

#endif
