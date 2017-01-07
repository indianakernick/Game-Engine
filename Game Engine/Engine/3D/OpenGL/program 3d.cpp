//
//  program 3d.cpp
//  Game Engine
//
//  Created by Indi Kernick on 29/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "program 3d.hpp"

#ifdef USE_OPENGL

void Graphics3D::ProgramOpenGL3D::load() {
  setupShaders("3d.vert", "3d.frag");
  
  model = getUniform("model");
  transInvModel = getUniform("transInvModel");
  mvp = getUniform("mvp");
  
  cameraDir = getUniform("cameraDir");
  
  diffuse = getUniform("diffuse");
  ambient = getUniform("ambient");
  specular = getUniform("specular");
  shininess = getUniform("shininess");
  diffuseTexture = getUniform("diffuseTexture");
  hasDiffuseTexture = getUniform("hasDiffuseTexture");
  
  lightIntensity = getUniform("lightIntensity");
  lightColor = getUniform("lightColor");
  lightPos = getUniform("lightPos");
  lightsNum = getUniform("lightsNum");
  
  pos = getAttr("pos");
  normal = getAttr("normal");
  texturePos = getAttr("texturePos");
}

void Graphics3D::ProgramOpenGL3D::enableAll() {
  glEnableVertexAttribArray(pos);
  glEnableVertexAttribArray(normal);
  glEnableVertexAttribArray(texturePos);
}

void Graphics3D::ProgramOpenGL3D::disableAll() {
  glDisableVertexAttribArray(pos);
  glDisableVertexAttribArray(normal);
  glDisableVertexAttribArray(texturePos);
}

void Graphics3D::ProgramOpenGL3D::enableTexturePos() {
  glEnableVertexAttribArray(texturePos);
}

void Graphics3D::ProgramOpenGL3D::disableTexturePos() {
  glDisableVertexAttribArray(texturePos);
}

void Graphics3D::ProgramOpenGL3D::posPointer(size_t stride, size_t offset) {
  glVertexAttribPointer(pos, 3, GL_FLOAT, GL_FALSE,
    static_cast<GLsizei>(stride),
    reinterpret_cast<const void *>(offset)
  );
}

void Graphics3D::ProgramOpenGL3D::normalPointer(size_t stride, size_t offset) {
  glVertexAttribPointer(normal, 3, GL_FLOAT, GL_FALSE,
    static_cast<GLsizei>(stride),
    reinterpret_cast<const void *>(offset)
  );
}

void Graphics3D::ProgramOpenGL3D::texturePosPointer(size_t stride, size_t offset) {
  glVertexAttribPointer(texturePos, 2, GL_FLOAT, GL_FALSE,
    static_cast<GLsizei>(stride),
    reinterpret_cast<const void *>(offset)
  );
}

void Graphics3D::ProgramOpenGL3D::setModel(const glm::mat4 &mat) {
  modelMat = mat;
}

void Graphics3D::ProgramOpenGL3D::setView(const glm::mat4 &mat) {
  viewMat = mat;
}

void Graphics3D::ProgramOpenGL3D::setProj(const glm::mat4 &mat) {
  projMat = mat;
}

void Graphics3D::ProgramOpenGL3D::setMat() {
  glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(modelMat));
  glm::mat4 transInvModelMat = glm::transpose(glm::inverse(modelMat));
  glUniformMatrix4fv(transInvModel, 1, GL_FALSE, glm::value_ptr(transInvModelMat));
  glm::vec3 cameraDirVec = glm::normalize(glm::vec3(glm::inverse(viewMat) * glm::vec4()));
  glUniform3f(cameraDir, cameraDirVec.x, cameraDirVec.y, cameraDirVec.z);
  glUniformMatrix4fv(mvp, 1, GL_FALSE, glm::value_ptr(projMat * viewMat * modelMat));
}

void Graphics3D::ProgramOpenGL3D::setMaterial(const Material &material) {
  glUniform3f(diffuse, material.diffuse.r, material.diffuse.g, material.diffuse.b);
  glUniform3f(ambient, material.ambient.r, material.ambient.g, material.ambient.b);
  glUniform3f(specular, material.specular.r, material.specular.g, material.specular.b);
  glUniform1f(shininess, material.shininess);
  if (material.diffuseTexture.isNull()) {
    diffuseTextureHandle = nullptr;
    glUniform1i(hasDiffuseTexture, false);
  } else {
    using namespace Resource::Descs;
    //keeping the handle until the draw call
    diffuseTextureHandle = app->cache->get(material.diffuseTexture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuseTextureHandle->getDesc<TextureOpenGL>()->getID());
    glUniform1i(diffuseTexture, 0);
    glUniform1i(hasDiffuseTexture, true);
  }
}

void Graphics3D::ProgramOpenGL3D::setLights(const std::vector<Light> &lights) {
  float *buffer = new float[lights.size() * 7];
  
  for (size_t i = 0; i < lights.size(); i++) {
    buffer[i] = lights[i].intensity;
    buffer[i * 3 + lights.size() + 0] = lights[i].color[0];
    buffer[i * 3 + lights.size() + 1] = lights[i].color[1];
    buffer[i * 3 + lights.size() + 2] = lights[i].color[2];
    buffer[i * 3 + lights.size() * 4 + 0] = lights[i].pos[0];
    buffer[i * 3 + lights.size() * 4 + 1] = lights[i].pos[1];
    buffer[i * 3 + lights.size() * 4 + 2] = lights[i].pos[2];
  }
  
  GLsizei size = static_cast<GLsizei>(lights.size());
  glUniform1fv(lightIntensity, size, buffer);
  glUniform3fv(lightColor, size, buffer + lights.size());
  glUniform3fv(lightPos, size, buffer + lights.size() * 4);
  glUniform1i(lightsNum, size);
  
  delete[] buffer;
}

#endif
