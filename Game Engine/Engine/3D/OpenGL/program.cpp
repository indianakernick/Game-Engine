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

void Graphics3D::ProgramOpenGL::bind() const {
  if (!linkStatus) {
    LOG_ERROR(RENDERING, "Tried to bind program \"%s\" that failed to link", name);
  } else {
    if (bound == id) {
      LOG_WARNING(RENDERING, "Tried to bind program \"%s\" but it was already bound", name);
    }
    glUseProgram(id);
    bound = id;
  }
}

void Graphics3D::ProgramOpenGL::unbind() const {
  if (bound == 0) {
    LOG_WARNING(RENDERING, "Tried to unbind program \"%s\" that was not bound", name);
  } else if (bound != id) {
    LOG_WARNING(RENDERING, "Tried to unbind program \"%s\" but another program was bound", name);
  }
  glUseProgram(0);
  bound = 0;
}

bool Graphics3D::ProgramOpenGL::isBound() const {
  return bound == id;
}

GLuint Graphics3D::ProgramOpenGL::getID() const {
  if (!glIsProgram(id)) {
    LOG_ERROR(RENDERING, "Program \"%s\" not initialized", name);
  }
  return id;
}

void Graphics3D::ProgramOpenGL::attach(const std::string &path) {
  Res::ID id("Shaders/" + path);
  Res::ShaderOpenGL::Ptr handle = resCache->get<Res::ShaderOpenGL>(id);
  glAttachShader(getID(), handle->getID());
}

void Graphics3D::ProgramOpenGL::setupShaders(const std::string &vertPath, const std::string &fragPath) {
  LOG_DEBUG(RENDERING, "Setting up shaders");
  
  attach(vertPath);
  attach(fragPath);
  
  link();
  printInfoLog();
}

GLint Graphics3D::ProgramOpenGL::getAttr(const char *attr) {
  if (!glIsProgram(id)) {
    LOG_ERROR(RENDERING, "Program \"%s\" not initialized", name);
  }
  if (!linkStatus) {
    LOG_ERROR(RENDERING, "Tried to get attribute of program \"%s\" that failed to link", name);
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
  if (!linkStatus) {
    LOG_ERROR(RENDERING, "Tried to get uniform of program \"%s\" that failed to link", name);
  }
  GLint location = glGetUniformLocation(id, uniform);
  if (location == -1) {
    LOG_ERROR(RENDERING, "Uniform \"%s\" not found in program \"%s\"", uniform, name);
  }
  return location;
}

void Graphics3D::ProgramOpenGL::enable(GLint attr) {
  glEnableVertexAttribArray(attr);
}

void Graphics3D::ProgramOpenGL::disable(GLint attr) {
  glDisableVertexAttribArray(attr);
}

void Graphics3D::ProgramOpenGL::enableArray(GLint attr, GLsizei size) {
  assert(size > 0);
  const GLint attrEnd = attr + size;
  for (GLint a = attr; a < attrEnd; a++) {
    glEnableVertexAttribArray(a);
  }
}

void Graphics3D::ProgramOpenGL::disableArray(GLint attr, GLsizei size) {
  assert(size > 0);
  const GLint attrEnd = attr + size;
  for (GLint a = attr; a < attrEnd; a++) {
    glDisableVertexAttribArray(a);
  }
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
