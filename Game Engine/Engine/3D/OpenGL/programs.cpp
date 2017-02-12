//
//  programs.cpp
//  Game Engine
//
//  Created by Indi Kernick on 9/2/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "programs.hpp"

#ifdef USE_OPENGL

size_t std::hash<Graphics3D::ProgType>::operator()(const Graphics3D::ProgType val) const {
  static std::hash<uint16_t> hasher;
  return hasher(*reinterpret_cast<const uint16_t *>(&val));
}

bool std::equal_to<Graphics3D::ProgType>::operator()(const Graphics3D::ProgType a,
                                                     const Graphics3D::ProgType b) const {
  return a.anim == b.anim && a.frag == b.frag;
}

Graphics3D::ProgramsOpenGL::ProgramsOpenGL() {
  /*
  just until i implement all of the shaders
  
  for (uint8_t a = 0; a < 2; a++) {
    for (uint8_t f = 0; f < 10; f++) {
      ProgType prog = {static_cast<bool>(a), static_cast<FragType>(f)};
      programs.emplace(prog, ProgramOpenGL(prog));
    }
  }*/
  ProgType prog = {true, FragType::PHONG};
  programs.emplace(prog, prog);
  
  glGenTextures(1, &whiteTex);
  glBindTexture(GL_TEXTURE_2D, whiteTex);
  const float white[4] = {1.0f, 1.0f, 1.0f, 1.0f};
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_FLOAT, white);
  
  glGenTextures(1, &blackTex);
  glBindTexture(GL_TEXTURE_2D, blackTex);
  const float black[4] = {0.0f, 0.0f, 0.0f, 0.0f};
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_FLOAT, black);
  
  glBindTexture(GL_TEXTURE_2D, 0);
}

Graphics3D::ProgramsOpenGL::~ProgramsOpenGL() {
  glDeleteTextures(1, &whiteTex);
  glDeleteTextures(1, &blackTex);
}

void Graphics3D::ProgramsOpenGL::loadAll() {
  for (auto p = programs.begin(); p != programs.end(); p++) {
    p->second.load();
  }
}

void Graphics3D::ProgramsOpenGL::bind(ProgType prog) {
  if (bound.anim != prog.anim || bound.frag != prog.frag) {
    bound = prog;
    boundID = programs.at(prog).getID();
    programs.at(prog).bind();
  }
}

#define LOC(name) glGetUniformLocation(boundID, #name)

void Graphics3D::ProgramsOpenGL::setModel(const glm::mat4 &model) {
  setUniform(LOC(model), model);
  setUniform(LOC(transInvModel), glm::transpose(glm::inverse(model)));
  setUniform(LOC(mvp), proj * view * model);
}

void Graphics3D::ProgramsOpenGL::setCamera(const glm::mat4 &newView,
                                           const glm::mat4 &newProj) {
  view = newView;
  proj = newProj;
  setUniform(LOC(cameraPos), glm::vec3(glm::inverse(view)[3]));
}

void Graphics3D::ProgramsOpenGL::setMaterial(const Material &material) {
  setUniform(LOC(diffuse), glm::vec3(material.diffuse));
  setUniform(LOC(ambient), glm::vec3(material.ambient));
  setUniform(LOC(specular), glm::vec3(material.specular));
  setUniform(LOC(shininess), material.shininess);
  
  if (material.diffuseTexture) {
    //keeping the handle until the draw call
    diffTex = resCache->get<Res::TextureOpenGL>(material.diffuseTexture);
    glActiveTexture(GL_TEXTURE0 + DIFF_TEX_UNIT);
    glBindTexture(GL_TEXTURE_2D, diffTex->getID());
  } else {
    diffTex = nullptr;
    glActiveTexture(GL_TEXTURE0 + DIFF_TEX_UNIT);
    glBindTexture(GL_TEXTURE_2D, whiteTex);
  }
  
  glActiveTexture(GL_TEXTURE0 + AMBI_TEX_UNIT);
  glBindTexture(GL_TEXTURE_2D, whiteTex);
  glActiveTexture(GL_TEXTURE0 + SPEC_TEX_UNIT);
  glBindTexture(GL_TEXTURE_2D, whiteTex);
  
  setUniform(LOC(diffuseTexture), 0);
  setUniform(LOC(ambientTexture), 1);
  setUniform(LOC(specularTexture), 2);
}

void Graphics3D::ProgramsOpenGL::setLights(
  const std::vector<Scene::Light::AllProps> &lights,
  const std::vector<glm::vec3> &lightsPos,
  const std::vector<glm::vec3> &lightsDir
) {
  Memory::Buffer buf(lights.size() * sizeof(lights[0].color));
  Memory::View<GLuint> ints(buf);
  Memory::View<GLfloat> floats(buf);
  //glm::vec3 is non-POD (that's really annoying)
  Memory::View<std::array<GLfloat, 3>> vec3s(buf);
  
  setUniformArray(LOC(lightPos), lightsPos);
  setUniformArray(LOC(lightDir), lightsDir);
  
  for (size_t i = 0; i < lights.size(); i++) {
    ints[i] = lights[i].type;
  }
  setUniformArrayPtr(LOC(lightType), lights.size(), ints.begin());
  
  for (size_t i = 0; i < lights.size(); i++) {
    vec3s[i][0] = lights[i].color.x;
    vec3s[i][1] = lights[i].color.y;
    vec3s[i][2] = lights[i].color.z;
  }
  setUniformArrayPtr(LOC(lightDiff), lights.size(),
                     reinterpret_cast<glm::vec3 *>(vec3s.begin()));
  
  for (size_t i = 0; i < lights.size(); i++) {
    floats[i] = lights[i].intensity;
  }
  setUniformArrayPtr(LOC(lightIntensity), lights.size(), floats.begin());
  
  for (size_t i = 0; i < lights.size(); i++) {
    floats[i] = lights[i].angle;
  }
  setUniformArrayPtr(LOC(lightAngle), lights.size(), floats.begin());
  
  setUniform(LOC(lightsNum), static_cast<GLuint>(lights.size()));
}

void Graphics3D::ProgramsOpenGL::setBones(const std::vector<glm::mat4> &bones) {
  assert(bones.size() <= MAX_BONES);
  setUniformArray(LOC(bones), bones);
}

/*
explcit uniform locations is a 4.3 feature and MacOS only support 4.1
maybe I should move to windows

void Graphics3D::ProgramsOpenGL::setModel(const glm::mat4 &model) {
  setUniform(MODEL_LOC, model);
  setUniform(TRANS_INV_MODEL_LOC, glm::transpose(glm::inverse(model)));
  setUniform(MVP_LOC, proj * view * model);
}

void Graphics3D::ProgramsOpenGL::setCamera(const glm::mat4 &newView,
                                           const glm::mat4 &newProj) {
  view = newView;
  proj = newProj;
  setUniform(CAM_POS_LOC, glm::vec3(glm::inverse(view)[3]));
}

void Graphics3D::ProgramsOpenGL::setMaterial(const Material &material) {
  setUniform(DIFFUSE_LOC, glm::vec3(material.diffuse));
  setUniform(AMBIENT_LOC, glm::vec3(material.ambient));
  setUniform(SPECULAR_LOC, glm::vec3(material.specular));
  setUniform(SHININESS_LOC, material.shininess);
  
  if (material.diffuseTexture) {
    //keeping the handle until the draw call
    diffTex = resCache->get<Res::TextureOpenGL>(material.diffuseTexture);
    glActiveTexture(GL_TEXTURE0 + DIFF_TEX_UNIT);
    glBindTexture(GL_TEXTURE_2D, diffTex->getID());
  } else {
    diffTex = nullptr;
    glActiveTexture(GL_TEXTURE0 + DIFF_TEX_UNIT);
    glBindTexture(GL_TEXTURE_2D, whiteTex);
  }
  
  glActiveTexture(GL_TEXTURE0 + AMBI_TEX_UNIT);
  glBindTexture(GL_TEXTURE_2D, whiteTex);
  glActiveTexture(GL_TEXTURE0 + SPEC_TEX_UNIT);
  glBindTexture(GL_TEXTURE_2D, whiteTex);
}

void Graphics3D::ProgramsOpenGL::setLights(
  const std::vector<Scene::Light::AllProps> &lights,
  const std::vector<glm::vec3> &lightsPos,
  const std::vector<glm::vec3> &lightsDir
) {
  Memory::Buffer buf(lights.size() * sizeof(lights[0].color));
  Memory::View<GLuint> ints(buf);
  Memory::View<GLfloat> floats(buf);
  //glm::vec3 is non-POD (that's really annoying)
  Memory::View<std::array<GLfloat, 3>> vec3s(buf);
  
  setUniformArray(L_POS_LOC, lightsPos);
  setUniformArray(L_DIR_LOC, lightsDir);
  
  for (size_t i = 0; i < lights.size(); i++) {
    ints[i] = lights[i].type;
  }
  setUniformArrayPtr(L_TYPE_LOC, lights.size(), ints.begin());
  
  for (size_t i = 0; i < lights.size(); i++) {
    vec3s[i][0] = lights[i].color.x;
    vec3s[i][1] = lights[i].color.y;
    vec3s[i][2] = lights[i].color.z;
  }
  setUniformArrayPtr(L_DIFF_LOC, lights.size(),
                     reinterpret_cast<glm::vec3 *>(vec3s.begin()));
  
  for (size_t i = 0; i < lights.size(); i++) {
    floats[i] = lights[i].intensity;
  }
  setUniformArrayPtr(L_INTENSITY_LOC, lights.size(), floats.begin());
  
  for (size_t i = 0; i < lights.size(); i++) {
    floats[i] = lights[i].angle;
  }
  setUniformArrayPtr(L_ANGLE_LOC, lights.size(), floats.begin());
  
  setUniform(L_NUM_LOC, static_cast<GLuint>(lights.size()));
}

void Graphics3D::ProgramsOpenGL::setBones(const std::vector<glm::mat4> &bones) {
  assert(bones.size() <= MAX_BONES);
  setUniformArray(BONES_LOC, bones);
}*/

#endif
