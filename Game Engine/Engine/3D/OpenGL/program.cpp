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
  Log::write(Log::RENDERING, Log::VERBOSE, "Linking program");

  glLinkProgram(id);
  printInfoLog();
}

void Graphics3D::ProgramOpenGL::bind() const {
  glUseProgram(id);
}

void Graphics3D::ProgramOpenGL::unbind() const {
  glUseProgram(0);
}

GLuint Graphics3D::ProgramOpenGL::getID() const {
  if (!glIsProgram(id)) {
    Log::write(Log::RENDERING, Log::ERROR,
      "getID called before program was initialized");
  }
  return id;
}

void Graphics3D::ProgramOpenGL::attach(const ShaderOpenGL &shader) {
  glAttachShader(getID(), shader.getID());
}

void Graphics3D::ProgramOpenGL::setupShaders(const std::string &vertPath, const std::string &fragPath) {
  Log::write(Log::RENDERING, Log::VERBOSE, "Setting up shaders");
  
  ShaderOpenGL vert(GL_VERTEX_SHADER);
  vert.load(vertPath);
  ShaderOpenGL frag(GL_FRAGMENT_SHADER);
  frag.load(fragPath);
  
  attach(vert);
  attach(frag);
  
  link();
  bind();
}

GLint Graphics3D::ProgramOpenGL::getAttr(const char *name) {
  if (!glIsProgram(id)) {
    Log::write(Log::RENDERING, Log::ERROR, "getAttr called on uninitialized program");
  }
  GLint location = glGetAttribLocation(id, name);
  if (location == -1) {
    Log::write(Log::RENDERING, Log::ERROR, "Attribute \"%s\" not found in program", name);
  }
  return location;
}

GLint Graphics3D::ProgramOpenGL::getUniform(const char *name) {
  if (!glIsProgram(id)) {
    Log::write(Log::RENDERING, Log::ERROR, "getUniform called on uninitialized program");
  }
  GLint location = glGetUniformLocation(id, name);
  if (location == -1) {
    Log::write(Log::RENDERING, Log::ERROR, "Uniform \"%s\" not found in program", name);
  }
  return location;
}

void Graphics3D::ProgramOpenGL::printInfoLog() {
  if (!glIsProgram(id)) {
    Log::write(Log::RENDERING, Log::ERROR, "Program not initialized when printInfoLog was called");
    return;
  }
  
  GLint status;
  glGetProgramiv(id, GL_LINK_STATUS, &status);
  if (status) {
    Log::write(Log::RENDERING, Log::INFO, "Successfully linked program");
  } else {
    Log::write(Log::RENDERING, Log::ERROR, "Failed to link program");
  }
  
  GLint length;
  glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
  char *log = new char[length];
  glGetProgramInfoLog(id, length, nullptr, log);
  Log::write(Log::RENDERING, Log::INFO, "Program info log:\n%s", log);
  delete [] log;
}

#endif
