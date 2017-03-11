//
//  renderer.cpp
//  Game Engine
//
//  Created by Indi Kernick on 15/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "renderer.hpp"

#ifdef USE_OPENGL

void Graphics3D::RendererOpenGL::init() {
  LOG_INFO(SCENE_GRAPH, "Initializing OpenGL scene renderer");
  programs = std::make_unique<ProgramsOpenGL>();
  programs->loadAll();
  programs->bind({false, FragType::SOLID});
  
  CHECK_OPENGL_ERROR();
}

void Graphics3D::RendererOpenGL::render(Scene::Root::Ptr root) {
  CHECK_OPENGL_ERROR();
  camera = root->getActiveCamera();
  if (camera == nullptr) {
    return;
  }
  CHECK_OPENGL_ERROR();
  programs->setCamera(camera->getView(), camera->getProj());
  CHECK_OPENGL_ERROR();
  sendLights(root->getLights());
  CHECK_OPENGL_ERROR();
  renderChildren(root->getChildren());
  CHECK_OPENGL_ERROR();
}

void Graphics3D::RendererOpenGL::quit() {
  LOG_INFO(SCENE_GRAPH, "Quitting OpenGL scene renderer");
  programs.reset();
}

void Graphics3D::RendererOpenGL::sendLights(const Scene::Root::Lights &lights) {
  static const glm::vec4 positiveZ {0.0f, 0.0f, 1.0f, 0.0f};
  
  std::vector<Scene::Light::AllProps> lightProps;
  lightProps.reserve(lights.size());
  std::vector<glm::vec3> lightsPos;
  lightsPos.reserve(lights.size());
  std::vector<glm::vec3> lightsDir;
  lightsDir.reserve(lights.size());
  
  for (auto i = lights.begin(); i != lights.end(); ++i) {
    lightProps.emplace_back((*i)->getAllProps());
    const glm::mat4 transform = getAbsTransform((*i).get());
    lightsPos.emplace_back(transform[3]);
    lightsDir.emplace_back(positiveZ * transform);
  }
  
  programs->setLights(lightProps, lightsPos, lightsDir);
}

void Graphics3D::RendererOpenGL::renderMesh(const Scene::Mesh::Ptr mesh) {
  Res::MeshOpenGL::Ptr meshHandle =
    resCache->get<Res::MeshOpenGL>(mesh->getMesh());
  
  const std::vector<GLuint> &VAOs = meshHandle->getVAOs();
  const std::vector<uint8_t> &matIndicies = meshHandle->getMatIndicies();
  const std::vector<Graphics3D::Material> &materials = meshHandle->getMaterials();
  const std::vector<unsigned> &indiciesNum = meshHandle->getIndiciesNum();
  const std::vector<Graphics3D::ProgType> &progTypes = meshHandle->getProgTypes();
  
  programs->setModel(stack.top());
  programs->setBones(anim->getBoneTransforms());
  
  for (size_t i = 0; i < indiciesNum.size(); i++) {
    glBindVertexArray(VAOs[i]);
    
    programs->bind(progTypes[i]);
    programs->setMaterial(materials[matIndicies[i]]);
    
    glDrawElements(GL_TRIANGLES,
                   indiciesNum[i],
                   Graphics3D::TypeEnum<ElemType>::type,
                   0);
  }
}

glm::mat4 Graphics3D::RendererOpenGL::getAbsTransform(const Scene::Node *node) {
  const Scene::Node *parent = node->getParent();
  if (parent) {
    return node->getToWorld() * getAbsTransform(parent);
  } else {
    return node->getToWorld();
  }
}

void Graphics3D::RendererOpenGL::renderChildren(const Scene::Node::Children &children) {
  for (auto i = children.begin(); i != children.end(); ++i) {
    const Scene::Node::Ptr child = *i;
    stack.push(child->getToWorld());
    renderNode(child);
    renderChildren(child->getChildren());
    stack.pop();
  }
}

void Graphics3D::RendererOpenGL::renderNode(const Scene::Node::Ptr node) {
  Scene::Mesh::Ptr mesh = std::dynamic_pointer_cast<Scene::Mesh>(node);
  if (mesh) {
    renderMesh(mesh);
  }
}

#endif
