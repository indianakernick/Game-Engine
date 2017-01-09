//
//  program.cpp
//  opengl
//
//  Created by Indi Kernick on 22/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "program.hpp"

#ifdef USE_OPENGL

Graphics3D::ProgramOpenGL::ProgramOpenGL() {
  id = glCreateProgram();
}

Graphics3D::ProgramOpenGL::~ProgramOpenGL() {
  glDeleteProgram(id);
}

void Graphics3D::ProgramOpenGL::link() {
  LOG_DEBUG(RENDERING, "Linking program");

  glLinkProgram(id);
  
  GLint status;
  glGetProgramiv(id, GL_LINK_STATUS, &status);
  if (status) {
    LOG_INFO(RENDERING, "Successfully linked program");
  } else {
    LOG_ERROR(RENDERING, "Failed to link program");
  }
}

void Graphics3D::ProgramOpenGL::validate() {
  LOG_DEBUG(RENDERING, "Validating program");
  
  glValidateProgram(id);
  
  GLint status;
  glGetProgramiv(id, GL_VALIDATE_STATUS, &status);
  if (status) {
    LOG_INFO(RENDERING, "Program is valid");
  } else {
    LOG_ERROR(RENDERING, "Program is invalid");
  }
}

void Graphics3D::ProgramOpenGL::bind() const {
  glUseProgram(id);
}

void Graphics3D::ProgramOpenGL::unbind() const {
  glUseProgram(0);
}

GLuint Graphics3D::ProgramOpenGL::getID() const {
  if (!glIsProgram(id)) {
    LOG_ERROR(RENDERING,
      "getID called before program was initialized");
  }
  return id;
}

void Graphics3D::ProgramOpenGL::attach(const std::string &path) {
  Resource::ID id("Shaders/" + path);
  Resource::Handle::Ptr handle = Global::resCache->get(id);
  Resource::Descs::ShaderOpenGL::Ptr desc =
    handle->getDesc<Resource::Descs::ShaderOpenGL>();
  
  glAttachShader(getID(), desc->getID());
}

void Graphics3D::ProgramOpenGL::setupShaders(const std::string &vertPath, const std::string &fragPath) {
  LOG_DEBUG(RENDERING, "Setting up shaders");
  
  attach(vertPath);
  attach(fragPath);
  
  link();
  validate();
  printInfoLog();
  
  bind();
}

GLint Graphics3D::ProgramOpenGL::getAttr(const char *name) {
  if (!glIsProgram(id)) {
    LOG_ERROR(RENDERING, "getAttr called on uninitialized program");
  }
  GLint location = glGetAttribLocation(id, name);
  if (location == -1) {
    LOG_ERROR(RENDERING, "Attribute \"%s\" not found in program", name);
  }
  return location;
}

GLint Graphics3D::ProgramOpenGL::getUniform(const char *name) {
  if (!glIsProgram(id)) {
    LOG_ERROR(RENDERING, "getUniform called on uninitialized program");
  }
  GLint location = glGetUniformLocation(id, name);
  if (location == -1) {
    LOG_ERROR(RENDERING, "Uniform \"%s\" not found in program", name);
  }
  return location;
}

void Graphics3D::ProgramOpenGL::printInfoLog() {
  if (!glIsProgram(id)) {
    LOG_ERROR(RENDERING, "Program not initialized when printInfoLog was called");
    return;
  }
  
  GLint length;
  glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
  if (length) {
    char *log = new char[length];
    glGetProgramInfoLog(id, length, nullptr, log);
    LOG_INFO(RENDERING, "Program info log:\n%s", log);
    delete [] log;
  } else {
    LOG_INFO(RENDERING, "Program didn't produce an info log");
  }
}

#endif
