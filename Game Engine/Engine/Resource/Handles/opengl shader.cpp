//
//  opengl shader.cpp
//  Game Engine
//
//  Created by Indi Kernick on 8/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "opengl shader.hpp"

#ifdef USE_OPENGL

Res::ShaderOpenGL::ShaderOpenGL(GLuint id, GLenum type)
  : id(id), type(type) {}

Res::ShaderOpenGL::~ShaderOpenGL() {
  glDeleteShader(id);
}

GLuint Res::ShaderOpenGL::getID() const {
  return id;
}

GLenum Res::ShaderOpenGL::getType() const {
  return type;
}

#endif
