//
//  opengl shader.cpp
//  Game Engine
//
//  Created by Indi Kernick on 8/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "opengl shader.hpp"

#ifdef USE_OPENGL

Resource::Handles::ShaderOpenGL::ShaderOpenGL(GLuint id, GLenum type)
  : id(id), type(type) {}

Resource::Handles::ShaderOpenGL::~ShaderOpenGL() {
  glDeleteShader(id);
}

GLuint Resource::Handles::ShaderOpenGL::getID() const {
  return id;
}

GLenum Resource::Handles::ShaderOpenGL::getType() const {
  return type;
}

#endif
