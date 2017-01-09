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

void Graphics3D::MeshNode::render(MatStack &stack, Program3D *program, std::shared_ptr<CameraNode>) {
  Resource::Handle::Ptr meshHandle = Global::resCache->get(mesh);
  Resource::Descs::MeshOpenGL::Ptr meshDesc =
    meshHandle->getDesc<Resource::Descs::MeshOpenGL>();
  
  ProgramOpenGL3D *programImpl = dynamic_cast<ProgramOpenGL3D *>(program);
  //this should never be null because of the USE_OPENGL macro
  assert(programImpl);
  
  programImpl->setModel(stack.top());
  programImpl->setMat();
  
  //they are only created if they need to be
  meshDesc->createVertexArrays(*programImpl);
  meshDesc->render(*programImpl);
}

#endif
