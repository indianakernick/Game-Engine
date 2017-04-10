//
//  shader program.cpp
//  Game Engine
//
//  Created by Indi Kernick on 8/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "shader program.hpp"

#ifdef USE_OPENGL

using namespace Platform;

ShaderProgramImpl::ShaderProgramImpl(const std::string &name, GLuint id)
  : ShaderProgram(name), id(id) {
  assert(id);
}

ShaderProgramImpl::~ShaderProgramImpl() {
  glDeleteProgram(id);
}

GLuint ShaderProgramImpl::getID() const {
  return id;
}

void ShaderProgramImpl::bind() {
  glUseProgram(id);
  CHECK_OPENGL_ERROR();
}

#endif
