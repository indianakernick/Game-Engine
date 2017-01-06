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
    Log::write(Log::RENDERING, Log::ERROR,
      "Failed to open file \"%s\"", path.c_str());
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
    Log::write(Log::RENDERING, Log::ERROR,
      "Shader \"%s\" not initialized when printInfoLog was called", name.c_str());
    return;
  }
  
  GLint status;
  glGetShaderiv(id, GL_COMPILE_STATUS, &status);
  if (status) {
    Log::write(Log::RENDERING, Log::INFO,
      "Successfully compiled shader \"%s\"", name.c_str());
  } else {
    Log::write(Log::RENDERING, Log::ERROR,
      "Failed to compile shader \"%s\"", name.c_str());
  }
  
  GLint length;
  glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
  char *log = new char[length];
  glGetShaderInfoLog(id, length, nullptr, log);
  Log::write(Log::RENDERING, Log::INFO,
    "Shader \"%s\" info log:\n%s", name.c_str(), log);
  delete [] log;
}

GLuint Graphics3D::ShaderOpenGL::getID() const {
  if (!glIsShader(id)) {
    Log::write(Log::RENDERING, Log::ERROR,
      "getID called before shader was initialized");
  }
  return id;
}

#endif
