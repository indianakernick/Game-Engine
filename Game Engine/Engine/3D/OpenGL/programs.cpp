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
  return combine(val.anim, val.frag, val.ui);
}

void makeTex(GLuint &id, const float *data) {
  glGenTextures(1, &id);
  glBindTexture(GL_TEXTURE_2D, id);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_FLOAT, data);
  
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
}

Graphics3D::ProgramsOpenGL::ProgramsOpenGL() {
  for (uint8_t a = 0; a < 2; a++) {
    for (uint8_t f = 0; f < static_cast<uint8_t>(FragType::_COUNT); f++) {
      const ProgType prog = {static_cast<bool>(a), static_cast<FragType>(f)};
      programs.emplace(prog, prog);
    }
  }
  
  static const float white[4] = {1.0f, 1.0f, 1.0f, 1.0f};
  makeTex(whiteTex, white);
  static const float black[4] = {0.0f, 0.0f, 0.0f, 0.0f};
  makeTex(blackTex, black);
  
  glBindTexture(GL_TEXTURE_2D, 0);
  
  CHECK_OPENGL_ERROR();
}

Graphics3D::ProgramsOpenGL::~ProgramsOpenGL() {
  glDeleteTextures(1, &whiteTex);
  glDeleteTextures(1, &blackTex);
}

void Graphics3D::ProgramsOpenGL::loadAll() {
  for (auto p = programs.begin(); p != programs.end(); p++) {
    p->second.load();
  }
  
  CHECK_OPENGL_ERROR();
}

void Graphics3D::ProgramsOpenGL::bind(ProgType prog) {
  if (boundID == 0 || bound != prog) {
    bound = prog;
    ProgramOpenGL &program = programs.at(prog);
    boundID = program.getID();
    program.bind();
  }
  
  CHECK_OPENGL_ERROR();
}

//explcit uniform locations is a 4.3 feature and MacOS only support 4.1
//maybe I should move to windows
#define LOC(name) glGetUniformLocation(boundID, #name)

void Graphics3D::ProgramsOpenGL::setModel(const glm::mat4 &model) {
  assert(!bound.ui);
  setUniform(LOC(model), model);
  setUniform(LOC(transInvModel), glm::transpose(glm::inverse(model)));
  setUniform(LOC(mvp), proj * view * model);
  
  CHECK_OPENGL_ERROR();
}

void Graphics3D::ProgramsOpenGL::setCamera(const glm::mat4 &newView,
                                           const glm::mat4 &newProj) {
  assert(!bound.ui);
  view = newView;
  proj = newProj;
  setUniform(LOC(cameraPos), glm::vec3(glm::inverse(view)[3]));
  
  CHECK_OPENGL_ERROR();
}

GLuint bindTex(Res::TextureOpenGL::Ptr &handle,
             const Res::ID &id,
             GLuint unit,
             GLuint defTex) {
  if (id) {
    handle = resCache->get<Res::TextureOpenGL>(id);
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, handle->getID());
    return handle->getID();
  } else {
    handle = nullptr;
    glActiveTexture(GL_TEXTURE0 + unit);
    glBindTexture(GL_TEXTURE_2D, defTex);
    return defTex;
  }
}

void Graphics3D::ProgramsOpenGL::setMaterial(const Material &material) {
  assert(!bound.ui);
  
  setUniform(LOC(diff), glm::vec3(material.diffuse));
  setUniform(LOC(ambi), glm::vec3(material.ambient));
  setUniform(LOC(spec), glm::vec3(material.specular));
  setUniform(LOC(shininess), material.shininess);
  
  GLuint boundTex = bindTex(diffTex, material.diffuseTexture, DIFF_TEX_UNIT, whiteTex);
  bindTex(ambiTex, material.ambientTexture, AMBI_TEX_UNIT, boundTex);
  bindTex(specTex, material.specularTexture, SPEC_TEX_UNIT, whiteTex);
  
  setUniform(LOC(diffTex), DIFF_TEX_UNIT);
  setUniform(LOC(ambiTex), AMBI_TEX_UNIT);
  setUniform(LOC(specTex), SPEC_TEX_UNIT);
  
  CHECK_OPENGL_ERROR();
}

void Graphics3D::ProgramsOpenGL::setLights(
  const std::vector<Scene::Light::AllProps> &lights,
  const std::vector<glm::vec3> &lightsPos,
  const std::vector<glm::vec3> &lightsDir
) {
  assert(!bound.ui);
  assert(lights.size() < MAX_LIGHTS);

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
  
  static const std::vector<glm::vec3> white(lights.size(), glm::vec3(1.0, 1.0, 1.0));
  static const std::vector<glm::vec3> black(lights.size(), glm::vec3(0.0, 0.0, 0.0));
  setUniformArray(LOC(lightAmbi), white);
  setUniformArray(LOC(lightSpec), white);
  
  for (size_t i = 0; i < lights.size(); i++) {
    floats[i] = lights[i].intensity;
  }
  setUniformArrayPtr(LOC(lightIntensity), lights.size(), floats.begin());
  
  for (size_t i = 0; i < lights.size(); i++) {
    floats[i] = lights[i].angle;
  }
  std::vector<float> zero(lights.size(), 0.0f);
  setUniformArray(LOC(lightInnerAngle), zero);
  setUniformArrayPtr(LOC(lightOuterAngle), lights.size(), floats.begin());
  
  setUniform(LOC(lightsNum), static_cast<GLuint>(lights.size()));
  
  CHECK_OPENGL_ERROR();
}

void Graphics3D::ProgramsOpenGL::setBones(const std::vector<glm::mat4> &bones) {
  assert(!bound.ui);
  assert(bones.size() <= MAX_BONES);
  setUniformArray(LOC(bones), bones);
  
  CHECK_OPENGL_ERROR();
}

#endif
