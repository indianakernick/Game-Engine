//
//  shader.cpp
//  opengl
//
//  Created by Indi Kernick on 21/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "shader.hpp"

#ifdef USE_OPENGL

Graphics3D::ShaderOpenGL::ShaderOpenGL(GLenum type) {
  id = glCreateShader(type);
}

Graphics3D::ShaderOpenGL::~ShaderOpenGL() {
  glDeleteShader(id);
}

void Graphics3D::ShaderOpenGL::load(const std::string &path) {
  name = path;

  std::ifstream file(path, std::ios::app);
  if (!file.is_open()) {
    std::cerr << "Failed to open file \"" << path << "\"\n";
    return;
  }
  const GLint size = static_cast<GLint>(file.tellg());
  file.seekg(0, std::ios::beg);
  char *buffer = new char[size];
  file.read(buffer, size);
  file.close();
  
  glShaderSource(id, 1, &buffer, &size);
  glCompileShader(id);
  
  delete[] buffer;
  printInfoLog();
}

void Graphics3D::ShaderOpenGL::printInfoLog() {
  if (!glIsShader(id)) {
    std::cerr << '\"' << name << "\" not initialized when printInfoLog was called\n";
  }
  
  GLint status;
  glGetShaderiv(id, GL_COMPILE_STATUS, &status);
  if (status) {
    std::cerr << "Successfully compiled \"" << name << "\"\n";
  } else {
    std::cerr << "Failed to compile \"" << name << "\"\n";
  }
  
  GLint length;
  glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
  char *log = new char[length];
  glGetShaderInfoLog(id, length, nullptr, log);
  std::cerr << '\"' << name << "\" info log:\n" << log << '\n';
  delete [] log;
}

GLuint Graphics3D::ShaderOpenGL::getID() const {
  if (!glIsShader(id)) {
    std::cerr << "getID called before shader was initialized\n";
  }
  return id;
}

#endif
