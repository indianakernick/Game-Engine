//
//  renderer.cpp
//  Game Engine
//
//  Created by Indi Kernick on 15/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "renderer.hpp"

#ifdef USE_OPENGL

void Scene::RendererOpenGL::init() {
  LOG_INFO(SCENE_GRAPH, "Initializing OpenGL scene renderer");
  phong.load();
  phong.bind();
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
}

void Scene::RendererOpenGL::render(Root::Ptr root) {
  camera = root->getActiveCamera();
  if (camera == nullptr) {
    return;
  }
  phong.setProj(camera->getProj());
  phong.setView(camera->getView());
  sendLights(root->getLights());
  renderChildren(root->getChildren());
}

void Scene::RendererOpenGL::quit() {
  LOG_INFO(SCENE_GRAPH, "Quitting OpenGL scene renderer");
  glBindVertexArray(0);
  glDeleteVertexArrays(1, &vao);
  phong.unbind();
}

void Scene::RendererOpenGL::sendLights(const Scene::Root::Lights &lights) {
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
  
  phong.setLights(lightProps, lightsPos, lightsDir);
}

void Scene::RendererOpenGL::renderMesh(const Scene::Mesh::Ptr mesh) {
  Res::MeshOpenGL::Ptr meshHandle =
    resCache->get<Res::MeshOpenGL>(mesh->getMesh());
  
  const std::vector<GLuint> &verts = meshHandle->getVerts();
  const std::vector<GLuint> &norms = meshHandle->getNorms();
  const std::vector<GLuint> &UVs = meshHandle->getUVs();
  const std::vector<bool> &hasUVs = meshHandle->getHasUVs();
  const std::vector<GLuint> &elems = meshHandle->getElems();
  const std::vector<uint8_t> &matIndicies = meshHandle->getMatIndicies();
  const std::vector<Graphics3D::Material> &materials = meshHandle->getMaterials();
  const std::vector<unsigned> &indiciesNum = meshHandle->getIndiciesNum();
  const std::vector<GLuint> &boneIDs = meshHandle->getBoneIDs();
  const std::vector<GLuint> &boneWeights = meshHandle->getBoneWeights();
  
  phong.setModel(stack.top());
  phong.setMat();
  const std::vector<glm::mat4> &transforms = anim->getBoneTransforms();
  phong.setBones(transforms);
  
  phong.enableAll();
  
  for (size_t i = 0; i < verts.size(); i++) {
    glBindBuffer(GL_ARRAY_BUFFER, verts[i]);
    phong.posPointer(3 * sizeof(float), 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, norms[i]);
    phong.normalPointer(3 * sizeof(float), 0);
    
    if (hasUVs[i]) {
      phong.enableTexturePos();
      glBindBuffer(GL_ARRAY_BUFFER, UVs[i]);
      phong.texturePosPointer(2 * sizeof(float), 0);
    } else {
      phong.disableTexturePos();
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, boneIDs[i]);
    phong.boneIDPointer();
    
    glBindBuffer(GL_ARRAY_BUFFER, boneWeights[i]);
    phong.boneWeightPointer();
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elems[i]);
  
    phong.setMaterial(materials[matIndicies[i]]);
    
    glDrawElements(GL_TRIANGLES,
                   indiciesNum[i],
                   Graphics3D::TypeEnum<Res::MeshOpenGL::ElementType>::type,
                   0);
  }
}

glm::mat4 Scene::RendererOpenGL::getAbsTransform(const Scene::Node *node) {
  const Scene::Node *parent = node->getParent();
  if (parent) {
    return node->getToWorld() * getAbsTransform(parent);
  } else {
    return node->getToWorld();
  }
}

void Scene::RendererOpenGL::renderChildren(const Scene::Node::Children &children) {
  for (auto i = children.begin(); i != children.end(); ++i) {
    const Scene::Node::Ptr child = *i;
    stack.push(child->getToWorld());
    renderNode(child);
    renderChildren(child->getChildren());
    stack.pop();
  }
}

void Scene::RendererOpenGL::renderNode(const Scene::Node::Ptr node) {
  Scene::Mesh::Ptr mesh = std::dynamic_pointer_cast<Scene::Mesh>(node);
  if (mesh) {
    renderMesh(mesh);
  }
}

#endif
