//
//  opengl shader.cpp
//  Game Engine
//
//  Created by Indi Kernick on 8/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "opengl shader.hpp"

#ifdef USE_OPENGL

using namespace Resource;

const std::string &Loaders::ShaderOpenGL::getName() {
  static const std::string NAME = "OpenGL shader";
  return NAME;
}

bool Loaders::ShaderOpenGL::canLoad(const std::string &fileExt) {
  vertShader = fileExt == "vert";
  return vertShader || fileExt == "frag";
}

Handle::Ptr Loaders::ShaderOpenGL::load(const ID &resID) {
  std::pair<Memory::Buffer, bool> filePair = readFile(resID);
  if (!filePair.second) {
    LOG_ERROR(RESOURCES, "Failed to open file \"%s\"", resID.getPathC());
    return nullptr;
  }
  
  GLenum type = GL_FRAGMENT_SHADER;
  if (vertShader) {
    type = GL_VERTEX_SHADER;
  }
  const char *typeName = type == GL_FRAGMENT_SHADER ? "fragment" : "vertex";
  
  GLuint id = glCreateShader(type);
  Handles::ShaderOpenGL::Ptr shader =
    std::make_shared<Handles::ShaderOpenGL>(id, type);
  
  if (id == 0 || !glIsShader(id)) {
    LOG_ERROR(RENDERING, 
      "Failed to create shader object: %s", gluErrorString(glGetError()));
    return nullptr;
  }
  
  const GLchar *string = reinterpret_cast<const GLchar *>(filePair.first.begin());
  const GLint length = static_cast<GLint>(filePair.first.size());
  glShaderSource(id, 1, &string, &length);
  glCompileShader(id);
  
  GLint status;
  glGetShaderiv(id, GL_COMPILE_STATUS, &status);
  if (status == GL_TRUE) {
    LOG_INFO(RENDERING, "Successfully compiled %s shader", typeName);
  } else {
    LOG_ERROR(RENDERING, "Failed to compile %s shader", typeName);
  }
  
  GLint logLength;
  glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);
  if (logLength) {
    char *log = new char[logLength];
    glGetShaderInfoLog(id, logLength, nullptr, log);
    LOG_INFO(RENDERING, "%s shader info log:\n%s", typeName, log);
    delete[] log;
  } else {
    LOG_INFO(RENDERING, "%s shader doesn't have an info log", typeName);
  }
  
  GLenum error = glGetError();
  if (error != GL_NO_ERROR) {
    LOG_ERROR(RENDERING, "Error loading shader: %s", gluErrorString(error));
    return nullptr;
  }
  
  /*
  It is possible to get the size of a fully compiled and linked program
  
  GLint size;
  glGetProgramiv(program, GL_PROGRAM_BINARY_LENGTH, &size);
  
  but not a compiled shader
  */
  shader->setSize(length);
  
  return shader;
}

#endif
