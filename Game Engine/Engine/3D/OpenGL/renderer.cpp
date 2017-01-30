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
  phong.load();
  phong.bind();
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
}

void Graphics3D::RendererOpenGL::render(Scene::Root::Ptr root) {
  camera = root->getActiveCamera();
  if (camera == nullptr) {
    return;
  }
  phong.setProj(camera->getProj());
  phong.setView(camera->getView());
  sendLights(root->getLights());
  renderChildren(root->getChildren());
}

void Graphics3D::RendererOpenGL::quit() {
  LOG_INFO(SCENE_GRAPH, "Quitting OpenGL scene renderer");
  glBindVertexArray(0);
  glDeleteVertexArrays(1, &vao);
  phong.unbind();
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
  
  phong.setLights(lightProps, lightsPos, lightsDir);
}

void Graphics3D::RendererOpenGL::renderMesh(const Scene::Mesh::Ptr mesh) {
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
    posPointer(0, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, norms[i]);
    normalPointer(0, 0);
    
    if (hasUVs[i]) {
      phong.enableTexturePos();
      glBindBuffer(GL_ARRAY_BUFFER, UVs[i]);
      texturePosPointer(0, 0);
    } else {
      phong.disableTexturePos();
    }
    
    glBindBuffer(GL_ARRAY_BUFFER, boneIDs[i]);
    boneIDPointer(0, 0);
    
    glBindBuffer(GL_ARRAY_BUFFER, boneWeights[i]);
    boneWeightPointer(0, 0);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elems[i]);
  
    phong.setMaterial(materials[matIndicies[i]]);
    
    glDrawElements(GL_TRIANGLES,
                   indiciesNum[i],
                   Graphics3D::TypeEnum<Res::MeshOpenGL::ElementType>::type,
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
