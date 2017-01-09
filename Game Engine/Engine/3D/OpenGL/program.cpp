//
//  program.cpp
//  opengl
//
//  Created by Indi Kernick on 22/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "program.hpp"

#ifdef USE_OPENGL

Graphics3D::ProgramOpenGL::ProgramOpenGL(const char *name)
  : id(glCreateProgram()), name(name) {}

Graphics3D::ProgramOpenGL::~ProgramOpenGL() {
  glDeleteProgram(id);
}

void Graphics3D::ProgramOpenGL::link() {
  LOG_DEBUG(RENDERING, "Linking program \"%s\"", name);

  glLinkProgram(id);
  
  GLint status;
  glGetProgramiv(id, GL_LINK_STATUS, &status);
  if (status) {
    LOG_INFO(RENDERING, "Successfully linked program \"%s\"", name);
    linkStatus = true;
  } else {
    LOG_ERROR(RENDERING, "Failed to link program \"%s\"", name);
  }
}

void Graphics3D::ProgramOpenGL::validate() {
  LOG_DEBUG(RENDERING, "Validating program \"%s\"", name);
  
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  
  glValidateProgram(id);
  
  glBindVertexArray(0);
  glDeleteVertexArrays(1, &vao);
  
  GLint status;
  glGetProgramiv(id, GL_VALIDATE_STATUS, &status);
  if (status) {
    LOG_INFO(RENDERING, "Successfully validated program \"%s\"", name);
  } else {
    LOG_ERROR(RENDERING, "Failed to validate program \"%s\"", name);
  }
}

void Graphics3D::ProgramOpenGL::bind() const {
  if (!linkStatus) {
    LOG_ERROR(RENDERING, "Tried to bind program \"%s\" that failed to link", name);
  }
  glUseProgram(id);
}

void Graphics3D::ProgramOpenGL::unbind() const {
  glUseProgram(0);
}

GLuint Graphics3D::ProgramOpenGL::getID() const {
  if (!glIsProgram(id)) {
    LOG_ERROR(RENDERING, "Program \"%s\" not initialized", name);
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

GLint Graphics3D::ProgramOpenGL::getAttr(const char *attr) {
  if (!glIsProgram(id)) {
    LOG_ERROR(RENDERING, "Program \"%s\" not initialized", name);
  }
  GLint location = glGetAttribLocation(id, attr);
  if (location == -1) {
    LOG_ERROR(RENDERING, "Attribute \"%s\" not found in program \"%s\"", attr, name);
  }
  return location;
}

GLint Graphics3D::ProgramOpenGL::getUniform(const char *uniform) {
  if (!glIsProgram(id)) {
    LOG_ERROR(RENDERING, "Program \"%s\" not initialized", name);
  }
  GLint location = glGetUniformLocation(id, uniform);
  if (location == -1) {
    LOG_ERROR(RENDERING, "Uniform \"%s\" not found in program \"%s\"", uniform, name);
  }
  return location;
}

void Graphics3D::ProgramOpenGL::printInfoLog() {
  if (!glIsProgram(id)) {
    LOG_ERROR(RENDERING, "Program \"%s\" not initialized", name);
    return;
  }
  
  GLint length;
  glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
  if (length) {
    char *log = new char[length];
    glGetProgramInfoLog(id, length, nullptr, log);
    LOG_INFO(RENDERING, "Program \"%s\" info log:\n%s", name, log);
    delete [] log;
  } else {
    LOG_INFO(RENDERING, "Program \"%s\" doesn't have an info log", name);
  }
}

#endif
