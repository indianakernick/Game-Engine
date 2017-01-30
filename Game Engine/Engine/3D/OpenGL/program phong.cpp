//
//  program phong.cpp
//  Game Engine
//
//  Created by Indi Kernick on 29/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "program phong.hpp"

#ifdef USE_OPENGL

Graphics3D::Phong::Phong(const char *name,
                         const char *vert,
                         const char *frag)
  : ProgramOpenGL(name), vert(vert), frag(frag) {}

void Graphics3D::Phong::load() {
  setupShaders(vert, frag);
  
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
}

void Graphics3D::Phong::enableAll() {
  enablePos();
  enableNormal();
  enableTexturePos();
}

void Graphics3D::Phong::disableAll() {
  disablePos();
  disableNormal();
  disableTexturePos();
}

void Graphics3D::Phong::enableTexturePos() {
  Graphics3D::enableTexturePos();
}

void Graphics3D::Phong::disableTexturePos() {
  Graphics3D::disableTexturePos();
}

void Graphics3D::Phong::setModel(const glm::mat4 &mat) {
  modelMat = mat;
}

void Graphics3D::Phong::setView(const glm::mat4 &mat) {
  viewMat = mat;
}

void Graphics3D::Phong::setProj(const glm::mat4 &mat) {
  projMat = mat;
}

void Graphics3D::Phong::setMat() {
  setUniform(model, modelMat);
  setUniform(transInvModel, glm::transpose(glm::inverse(modelMat)));
  setUniform(cameraPos, glm::vec3(glm::inverse(viewMat)[3]));
  setUniform(mvp, projMat * viewMat * modelMat);
}

void Graphics3D::Phong::setMaterial(const Material &material) {
  setUniform(diffuse, glm::vec3(material.diffuse));
  setUniform(ambient, glm::vec3(material.ambient));
  setUniform(specular, glm::vec3(material.specular));
  setUniform(shininess, material.shininess);
  if (material.diffuseTexture) {
    //keeping the handle until the draw call
    diffuseTextureHandle =
      resCache->get<Res::TextureOpenGL>(material.diffuseTexture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, diffuseTextureHandle->getID());
    setUniform(diffuseTexture, 0);
    setUniform(hasDiffuseTexture, true);
  } else {
    diffuseTextureHandle = nullptr;
    setUniform(hasDiffuseTexture, false);
  }
}

void Graphics3D::Phong::setLights(const std::vector<Scene::Light::AllProps> &lights,
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
