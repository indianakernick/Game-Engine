//
//  program phong.cpp
//  Game Engine
//
//  Created by Indi Kernick on 29/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "program phong.hpp"

#ifdef USE_OPENGL

Graphics3D::GLProgs::Phong::Phong()
  : ProgramOpenGL("Phong") {}

void Graphics3D::GLProgs::Phong::load() {
  setupShaders("phong.vert", "phong.frag");
  
  model = getUniform("model");
  transInvModel = getUniform("transInvModel");
  mvp = getUniform("mvp");
  
  cameraPos = getUniform("cameraPos");
  
  diffuse = getUniform("diffuse");
  ambient = getUniform("ambient");
  specular = getUniform("specular");
  shininess = getUniform("shininess");
  diffuseTexture = getUniform("diffuseTexture");
  hasDiffuseTexture = getUniform("hasDiffuseTexture");
  
  lightType = getUniform("lightType");
  lightColor = getUniform("lightColor");
  lightIntensity = getUniform("lightIntensity");
  lightHoriAngle = getUniform("lightHoriAngle");
  lightVertAngle = getUniform("lightVertAngle");
  lightPos = getUniform("lightPos");
  lightDir = getUniform("lightDir");
  lightsNum = getUniform("lightsNum");
  
  pos = getAttr("pos");
  normal = getAttr("normal");
  texturePos = getAttr("texturePos");
}

void Graphics3D::GLProgs::Phong::enableAll() {
  glEnableVertexAttribArray(pos);
  glEnableVertexAttribArray(normal);
  glEnableVertexAttribArray(texturePos);
}

void Graphics3D::GLProgs::Phong::disableAll() {
  glDisableVertexAttribArray(pos);
  glDisableVertexAttribArray(normal);
  glDisableVertexAttribArray(texturePos);
}

void Graphics3D::GLProgs::Phong::enableTexturePos() {
  glEnableVertexAttribArray(texturePos);
}

void Graphics3D::GLProgs::Phong::disableTexturePos() {
  glDisableVertexAttribArray(texturePos);
}

void Graphics3D::GLProgs::Phong::posPointer(size_t stride, size_t offset) {
  attribPointer<GLfloat[3]>(pos, stride, offset);
}

void Graphics3D::GLProgs::Phong::normalPointer(size_t stride, size_t offset) {
  attribPointer<GLfloat[3]>(normal, stride, offset);
}

void Graphics3D::GLProgs::Phong::texturePosPointer(size_t stride, size_t offset) {
  attribPointer<GLfloat[2]>(texturePos, stride, offset);
}

void Graphics3D::GLProgs::Phong::setModel(const glm::mat4 &mat) {
  modelMat = mat;
}

void Graphics3D::GLProgs::Phong::setView(const glm::mat4 &mat) {
  viewMat = mat;
}

void Graphics3D::GLProgs::Phong::setProj(const glm::mat4 &mat) {
  projMat = mat;
}

void Graphics3D::GLProgs::Phong::setMat() {
  glUniformMatrix4fv(model, 1, GL_FALSE, glm::value_ptr(modelMat));
  glm::mat4 transInvModelMat = glm::transpose(glm::inverse(modelMat));
  glUniformMatrix4fv(transInvModel, 1, GL_FALSE, glm::value_ptr(transInvModelMat));
  glm::vec3 cameraPosVec = glm::vec3(glm::inverse(viewMat)[3]);
  glUniform3f(cameraPos, cameraPosVec.x, cameraPosVec.y, cameraPosVec.z);
  glUniformMatrix4fv(mvp, 1, GL_FALSE, glm::value_ptr(projMat * viewMat * modelMat));
}

void Graphics3D::GLProgs::Phong::setMaterial(const Material &material) {
  glUniform3f(diffuse, material.diffuse.r, material.diffuse.g, material.diffuse.b);
  glUniform3f(ambient, material.ambient.r, material.ambient.g, material.ambient.b);
  glUniform3f(specular, material.specular.r, material.specular.g, material.specular.b);
  glUniform1f(shininess, material.shininess);
  if (material.diffuseTexture) {
    //keeping the handle until the draw call
    diffuseTextureHandle =
      Global::resCache->get<ResHnds::TextureOpenGL>(material.diffuseTexture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuseTextureHandle->getID());
    glUniform1i(diffuseTexture, 0);
    glUniform1i(hasDiffuseTexture, true);
  } else {
    diffuseTextureHandle = nullptr;
    glUniform1i(hasDiffuseTexture, false);
  }
}

void Graphics3D::GLProgs::Phong::setLights(const std::vector<Scene::Light::AllProps> &lights,
                                           const std::vector<glm::vec3> &lightsPos,
                                           const std::vector<glm::vec3> &lightsDir) {
  int *types = new int[lights.size()];
  float *buffer = new float[lights.size() * 6];
  
  const size_t color = 0;
  const size_t intensity = lights.size() * 3;
  const size_t horiAngle = lights.size() * 4;
  const size_t vertAngle = lights.size() * 5;
  
  for (size_t i = 0; i < lights.size(); i++) {
    types[i] = lights[i].type;
    buffer[color + i * 3 + 0] = lights[i].color[0];
    buffer[color + i * 3 + 1] = lights[i].color[1];
    buffer[color + i * 3 + 2] = lights[i].color[2];
    buffer[intensity + i] = lights[i].intensity;
    buffer[horiAngle + i] = lights[i].horiAngle;
    buffer[vertAngle + i] = lights[i].vertAngle;
  }
  
  const GLsizei size = static_cast<GLsizei>(lights.size());
  glUniform1iv(lightType, size, types);
  glUniform3fv(lightColor, size, buffer + color);
  glUniform1fv(lightIntensity, size, buffer + intensity);
  glUniform1fv(lightHoriAngle, size, buffer + horiAngle);
  glUniform1fv(lightVertAngle, size, buffer + vertAngle);
  glUniform3fv(lightPos, size, &lightsPos[0][0]);
  glUniform3fv(lightDir, size, &lightsDir[0][0]);
  glUniform1i(lightsNum, size);
  
  delete[] buffer;
  delete[] types;
}

#endif
