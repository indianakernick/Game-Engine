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
  : id(other.id), linkOK(other.linkOK), type(other.type) {
  other.id = 0;
}

Graphics3D::ProgramOpenGL::~ProgramOpenGL() {
  glDeleteProgram(id);
}

Graphics3D::ProgramOpenGL &Graphics3D::ProgramOpenGL::operator=(ProgramOpenGL &&other) {
  glDeleteProgram(id);
  id = other.id;
  other.id = 0;
  linkOK = other.linkOK;
  type = other.type;
  return *this;
}

void Graphics3D::ProgramOpenGL::load() {
  LOG_DEBUG(RENDERING, "Loading program %s", getName().c_str());
  
  Shaders shaders = getShaders(type);
  GLuint vertID = attach(shaders.vert);
  GLuint fragID = attach(shaders.frag);
 
  link();
  
  glDetachShader(id, vertID);
  glDetachShader(id, fragID);
  
  printInfoLog();
}

void Graphics3D::ProgramOpenGL::bind() const {
  if (!linkOK) {
    LOG_ERROR(RENDERING, "Tried to bind program %s that failed to link", getName().c_str());
  } else {
    if (bound == id) {
      LOG_WARNING(RENDERING, "Tried to bind program %s but it was already bound", getName().c_str());
    }
    glUseProgram(id);
    bound = id;
  }
}

void Graphics3D::ProgramOpenGL::unbind() const {
  if (bound == 0) {
    LOG_WARNING(RENDERING, "Tried to unbind program %s that was not bound", getName().c_str());
  } else if (bound != id) {
    LOG_WARNING(RENDERING, "Tried to unbind program %s but another program was bound", getName().c_str());
  }
  glUseProgram(0);
  bound = 0;
}

bool Graphics3D::ProgramOpenGL::isBound() const {
  return bound == id;
}

GLuint Graphics3D::ProgramOpenGL::getID() const {
  if (!glIsProgram(id)) {
    LOG_ERROR(RENDERING, "Program %s not initialized", getName().c_str());
  }
  return id;
}

GLuint Graphics3D::ProgramOpenGL::attach(const Res::ID &shader) {
  const Res::ShaderOpenGL::Ptr res = resCache->get<Res::ShaderOpenGL>(shader);
  const GLuint shaderID = res->getID();
  glAttachShader(id, shaderID);
  return shaderID;
}

void Graphics3D::ProgramOpenGL::link() {
  LOG_DEBUG(RENDERING, "Linking program %s", getName().c_str());

  glLinkProgram(id);
  
  GLint status;
  glGetProgramiv(id, GL_LINK_STATUS, &status);
  if (status) {
    LOG_INFO(RENDERING, "Successfully linked program %s", getName().c_str());
    linkOK = true;
  } else {
    LOG_ERROR(RENDERING, "Failed to link program %s", getName().c_str());
    linkOK = false;
  }
}

void Graphics3D::ProgramOpenGL::printInfoLog() {
  if (!glIsProgram(id)) {
    LOG_ERROR(RENDERING, "Program %s not initialized", getName().c_str());
    return;
  }
  
  GLint length;
  glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
  if (length) {
    char *log = new char[length];
    glGetProgramInfoLog(id, length, nullptr, log);
    LOG_INFO(RENDERING, "Program %s info log:\n%s", getName().c_str(), log);
    delete[] log;
  } else {
    LOG_INFO(RENDERING, "Program %s doesn't have an info log", getName().c_str());
  }
}

void getNameHelper(std::string &name, const Res::ID &shader) {
  if (!shader) {
    return;
  }
  name += shader.getPath() + " ";
  const Any &data = shader.getData();
  if (data.is<Res::ID>()) {
    name += data.as<Res::ID>().getPath() + " ";
  }
}

std::string Graphics3D::ProgramOpenGL::getName() const {
  Shaders shaders = getShaders(type);
  std::string name;
  getNameHelper(name, shaders.vert);
  getNameHelper(name, shaders.frag);
  return name;
}

#endif
