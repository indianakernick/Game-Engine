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
  
  Shaders shaders = getShaders();
  GLuint ids[shaders.size()];
  
  for (size_t s = 0; s < shaders.size(); s++) {
    const Res::ShaderOpenGL::Ptr shader =
      resCache->get<Res::ShaderOpenGL>(shaders[s]);
    ids[s] = shader->getID();
    glAttachShader(id, shader->getID());
  }
 
  link();
  
  for (size_t s = 0; s < shaders.size(); s++) {
    glDetachShader(id, ids[s]);
  }
  
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

Graphics3D::ProgramOpenGL::Shaders Graphics3D::ProgramOpenGL::getShaders() const {
  Shaders out;
  out[0] = Res::ID(type.anim ? "Shaders/anim.vert" : "Shaders/no anim.vert");
  out[1] = Res::ID("Shaders/common.frag");
  
  switch (type.frag) {
    case FragType::PHONG:
      out[2] = Res::ID("Shaders/phong.frag");
      break;
    case FragType::BLINN:
      out[2] = Res::ID("Shaders/blinn.frag");
      break;
    case FragType::TOON:
      //this has to be inmplemented with multiple programs
      break;
    case FragType::OREN_NAYER:
      out[2] = Res::ID("Shaders/oren nayer.frag");
      break;
    case FragType::MINNAERT:
      out[2] = Res::ID("Shaders/minnaert.frag");
      break;
    case FragType::COOK_TORRANCE:
      out[2] = Res::ID("Shaders/cook torrance.frag");
      break;
    case FragType::SOLID:
      out[2] = Res::ID("Shaders/solid.frag");
      break;
    case FragType::FRESNEL:
      out[2] = Res::ID("Shaders/fresnel.frag");
    
    default:
      LOG_ERROR(RENDERING, "Invalid program type");
  }
  
  return out;
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

std::string Graphics3D::ProgramOpenGL::getName() const {
  Shaders shaders = getShaders();
  std::string name = "\"";
  for (size_t s = 0; s < shaders.size(); s++) {
    name += shaders[s].getPath();
    if (s != shaders.size() - 1) {
      name += "\", \"";
    }
  }
  name += "\"";
  return name;
}

#endif
