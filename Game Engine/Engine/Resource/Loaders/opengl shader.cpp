//
//  opengl shader.cpp
//  Game Engine
//
//  Created by Indi Kernick on 8/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "opengl shader.hpp"

#ifdef USE_OPENGL

using namespace Res;

const std::string &ShaderLoaderOpenGL::getName() {
  static const std::string NAME = "OpenGL shader";
  return NAME;
}

bool ShaderLoaderOpenGL::canLoad(const std::string &fileExt) {
  return fileExt == "vert" ||
         fileExt == "frag" ||
         fileExt == "geom";
}

Handle::Ptr ShaderLoaderOpenGL::load(const ID &resID) {
  std::pair<Memory::Buffer, bool> filePair = readFile(resID);
  if (!filePair.second) {
    LOG_ERROR(RESOURCES, "Failed to open file \"%s\"", resID.getPathC());
    return nullptr;
  }
  
  const GLenum type = getType(resID.getExt());
  const GLuint id = glCreateShader(type);
  ShaderOpenGL::Ptr shader = std::make_shared<ShaderOpenGL>(id, type);
  
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
    LOG_INFO(RENDERING, "Successfully compiled shader \"%s\"", resID.getPathC());
  } else {
    LOG_ERROR(RENDERING, "Failed to compile shader \"%s\"", resID.getPathC());
  }
  
  GLint logLength;
  glGetShaderiv(id, GL_INFO_LOG_LENGTH, &logLength);
  if (logLength) {
    char *log = new char[logLength];
    glGetShaderInfoLog(id, logLength, nullptr, log);
    LOG_INFO(RENDERING, "Shader \"%s\" info log:\n%s", resID.getPathC(), log);
    delete[] log;
  } else {
    LOG_INFO(RENDERING, "Shader \"%s\" doesn't have an info log", resID.getPathC());
  }
  
  const GLenum error = glGetError();
  if (error != GL_NO_ERROR) {
    LOG_ERROR(RENDERING,
      "Error loading shader \"%s\": %s",
      resID.getPathC(), gluErrorString(error));
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

GLenum ShaderLoaderOpenGL::getType(const std::string &ext) {
  if (ext == "vert") {
    return GL_VERTEX_SHADER;
  } else if (ext == "frag") {
    return GL_FRAGMENT_SHADER;
  } else {
    return GL_GEOMETRY_SHADER;
  }
}

#endif
