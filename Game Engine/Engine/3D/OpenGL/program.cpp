//
//  program.cpp
//  opengl
//
//  Created by Indi Kernick on 22/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "program.hpp"

#ifdef USE_OPENGL

GLuint Graphics3D::ProgramOpenGL::bound = 0;

Graphics3D::ProgramOpenGL::ProgramOpenGL(ProgType type)
  : id(glCreateProgram()), type(type) {}

Graphics3D::ProgramOpenGL::ProgramOpenGL(ProgramOpenGL &&other)
  : id(other.id), linkStatus(other.linkStatus), type(other.type) {
  other.id = 0;
}

Graphics3D::ProgramOpenGL::~ProgramOpenGL() {
  glDeleteProgram(id);
}

Graphics3D::ProgramOpenGL &Graphics3D::ProgramOpenGL::operator=(ProgramOpenGL &&other) {
  glDeleteProgram(id);
  id = other.id;
  other.id = 0;
  linkStatus = other.linkStatus;
  type = other.type;
  return *this;
}

void Graphics3D::ProgramOpenGL::load() {
  LOG_DEBUG(RENDERING, "Loading program");
  
  std::pair<Res::ID, Res::ID> shaders = getShaders();
  const Res::ShaderOpenGL::Ptr vertShader = resCache->get<Res::ShaderOpenGL>(shaders.first);
  glAttachShader(id, vertShader->getID());
  const Res::ShaderOpenGL::Ptr fragShader = resCache->get<Res::ShaderOpenGL>(shaders.second);
  glAttachShader(id, fragShader->getID());
 
  link();
  printInfoLog();
}

void Graphics3D::ProgramOpenGL::bind() const {
  if (!linkStatus) {
    LOG_ERROR(RENDERING, "Tried to bind program \"%s\" that failed to link", getName().c_str());
  } else {
    if (bound == id) {
      LOG_WARNING(RENDERING, "Tried to bind program \"%s\" but it was already bound", getName().c_str());
    }
    glUseProgram(id);
    bound = id;
  }
}

void Graphics3D::ProgramOpenGL::unbind() const {
  if (bound == 0) {
    LOG_WARNING(RENDERING, "Tried to unbind program \"%s\" that was not bound", getName().c_str());
  } else if (bound != id) {
    LOG_WARNING(RENDERING, "Tried to unbind program \"%s\" but another program was bound", getName().c_str());
  }
  glUseProgram(0);
  bound = 0;
}

bool Graphics3D::ProgramOpenGL::isBound() const {
  return bound == id;
}

GLuint Graphics3D::ProgramOpenGL::getID() const {
  if (!glIsProgram(id)) {
    LOG_ERROR(RENDERING, "Program \"%s\" not initialized", getName().c_str());
  }
  return id;
}

std::pair<Res::ID, Res::ID> Graphics3D::ProgramOpenGL::getShaders() const {
  Res::ID vert(type.anim ? "Shaders/anim.vert" : "Shaders/no anim.vert");
  
  switch (type.frag) {
    case FragType::FLAT:
      return {vert, Res::ID("Shaders/flat.frag")};
    case FragType::GOURAUD:
      return {Res::ID("Shaders/gouraud.vert"), Res::ID("Shaders/gouraud.frag")};
    case FragType::PHONG:
      return {vert, Res::ID("Shaders/phong.frag")};
    case FragType::BLINN:
      return {vert, Res::ID("Shaders/blinn.frag")};
    case FragType::TOON:
      return {Res::ID("Shaders/toon.vert"), Res::ID("Shaders/toon.frag")};
    case FragType::OREN_NAYER:
      return {vert, Res::ID("Shaders/oren nayer.frag")};
    case FragType::MINNAERT:
      return {vert, Res::ID("Shaders/minnaert.frag")};
    case FragType::COOK_TORRENCE:
      return {vert, Res::ID("Shaders/cook torrence.frag")};
    case FragType::SOLID:
      return {vert, Res::ID("Shaders/solid.frag")};
    case FragType::FRESNEL:
      return {vert, Res::ID("Shaders/fresnel.frag")};
    
    default:
      LOG_ERROR(RENDERING, "Invalid program type");
  }
}

void Graphics3D::ProgramOpenGL::link() {
  LOG_DEBUG(RENDERING, "Linking program \"%s\"", getName().c_str());

  glLinkProgram(id);
  
  GLint status;
  glGetProgramiv(id, GL_LINK_STATUS, &status);
  if (status) {
    LOG_INFO(RENDERING, "Successfully linked program \"%s\"", getName().c_str());
    linkStatus = true;
  } else {
    LOG_ERROR(RENDERING, "Failed to link program \"%s\"", getName().c_str());
  }
}

void Graphics3D::ProgramOpenGL::printInfoLog() {
  if (!glIsProgram(id)) {
    LOG_ERROR(RENDERING, "Program \"%s\" not initialized", getName().c_str());
    return;
  }
  
  GLint length;
  glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
  if (length) {
    char *log = new char[length];
    glGetProgramInfoLog(id, length, nullptr, log);
    LOG_INFO(RENDERING, "Program \"%s\" info log:\n%s", getName().c_str(), log);
    delete[] log;
  } else {
    LOG_INFO(RENDERING, "Program \"%s\" doesn't have an info log", getName().c_str());
  }
}

std::string Graphics3D::ProgramOpenGL::getName() const {
  std::pair<Res::ID, Res::ID> shaders = getShaders();
  return shaders.first.getPath() + "  " + shaders.second.getPath();
}

#endif
