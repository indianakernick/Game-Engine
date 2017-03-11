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

const std::string &ShaderLoaderOpenGL::getName() const {
  static const std::string NAME = "OpenGL shader";
  return NAME;
}

bool ShaderLoaderOpenGL::canLoad(const std::string &ext) const {
  return ext == "vert" ||
         ext == "frag" ||
         ext == "geom";
}

Handle::Ptr ShaderLoaderOpenGL::load(const ID &resID) const {
  const GLenum type = getType(resID.getExt());
  const GLuint id = glCreateShader(type);
  ShaderOpenGL::Ptr shader = std::make_shared<ShaderOpenGL>(id, type);
  
  CHECK_OPENGL_ERROR();
  
  const GLint sourceLength = uploadSource(id, resID);
  compile(id, resID);
  printInfoLog(id, resID);
  
  CHECK_OPENGL_ERROR();
  
  /*
  It is possible to get the size of a fully compiled and linked program
  
  GLint size;
  glGetProgramiv(program, GL_PROGRAM_BINARY_LENGTH, &size);
  
  but not a compiled shader
  */
  shader->setSize(sourceLength);
  
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

GLint ShaderLoaderOpenGL::uploadSource(GLuint id, const Res::ID &resID) {
  const Any &data = resID.getData();
  const Memory::Buffer file = readFile(resID);
  
  if (data.is<Res::ID>()) {
    const Memory::Buffer otherFile = readFile(data.as<Res::ID>());
    const GLchar *strs[2] = {
      file.cbegin<GLchar>(),
      otherFile.cbegin<GLchar>()
    };
    const GLint lengths[2] = {
      static_cast<GLint>(file.size()),
      static_cast<GLint>(otherFile.size())
    };
    
    glShaderSource(id, 2, strs, lengths);
    
    return lengths[0] + lengths[1];
  } else {
    const GLchar *str = file.cbegin<GLchar>();
    const GLint length = static_cast<GLint>(file.size());
    
    glShaderSource(id, 1, &str, &length);
    
    return length;
  }
}

void ShaderLoaderOpenGL::compile(GLuint id, const Res::ID &resID) {
  glCompileShader(id);
  
  GLint status;
  glGetShaderiv(id, GL_COMPILE_STATUS, &status);
  if (status == GL_TRUE) {
    LOG_INFO(RENDERING, "Successfully compiled shader \"%s\"", resID.getPathC());
  } else {
    LOG_ERROR(RENDERING, "Failed to compile shader \"%s\"", resID.getPathC());
  }
}

void ShaderLoaderOpenGL::printInfoLog(GLuint id, const Res::ID &resID) {
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
}

#endif
