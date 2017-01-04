//
//  program.cpp
//  opengl
//
//  Created by Indi Kernick on 22/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "program.hpp"

#ifdef __gl_h_

Graphics3D::ProgramOpenGL::ProgramOpenGL() {
  id = glCreateProgram();
}

Graphics3D::ProgramOpenGL::~ProgramOpenGL() {
  glDeleteProgram(id);
}

void Graphics3D::ProgramOpenGL::link() {
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
    std::cerr << "getID called before program was initialized\n";
  }
  return id;
}

void Graphics3D::ProgramOpenGL::attach(const ShaderOpenGL &shader) {
  glAttachShader(getID(), shader.getID());
}

void Graphics3D::ProgramOpenGL::setupShaders(const std::string &vertPath, const std::string &fragPath) {
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
    std::cerr << "getAttr called on uninitialized program\n";
  }
  GLint location = glGetAttribLocation(id, name);
  if (location == -1) {
    std::cerr << "Attribute \"" << name << "\" not found in program\n";
  }
  return location;
}

GLint Graphics3D::ProgramOpenGL::getUniform(const char *name) {
  if (!glIsProgram(id)) {
    std::cerr << "getUniform called on uninitialized program\n";
  }
  GLint location = glGetUniformLocation(id, name);
  if (location == -1) {
    std::cerr << "Uniform \"" << name << "\" not found in program\n";
  }
  return location;
}

void Graphics3D::ProgramOpenGL::printInfoLog() {
  if (!glIsProgram(id)) {
    std::cerr << "Program not initialized when printInfoLog was called\n";
  }
  
  GLint status;
  glGetProgramiv(id, GL_LINK_STATUS, &status);
  if (status) {
    std::cerr << "Successfully linked program\n";
  } else {
    std::cerr << "Failed to link program\n";
  }
  
  GLint length;
  glGetProgramiv(id, GL_INFO_LOG_LENGTH, &length);
  char *log = new char[length];
  glGetProgramInfoLog(id, length, nullptr, log);
  std::cerr << "Program info log:\n" << log << '\n';
  delete [] log;
}

#endif
