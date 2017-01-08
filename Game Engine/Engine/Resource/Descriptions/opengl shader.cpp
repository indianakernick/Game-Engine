//
//  opengl shader.cpp
//  Game Engine
//
//  Created by Indi Kernick on 8/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "opengl shader.hpp"

Resource::Descs::ShaderOpenGL::ShaderOpenGL(GLuint id, GLenum type)
  : id(id), type(type) {}

Resource::Descs::ShaderOpenGL::~ShaderOpenGL() {
  glDeleteShader(id);
}

GLuint Resource::Descs::ShaderOpenGL::getID() const {
  return id;
}

GLenum Resource::Descs::ShaderOpenGL::getType() const {
  return type;
}
