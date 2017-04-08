//
//  shader.cpp
//  Game Engine
//
//  Created by Indi Kernick on 6/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "shader.hpp"

#ifdef USE_OPENGL

using namespace Platform;

ShaderImpl::ShaderImpl(Type type, GLuint id)
  : Shader(type), id(id) {
  assert(id);
}

ShaderImpl::~ShaderImpl() {
  glDeleteShader(id);
}

GLuint ShaderImpl::getID() const {
  return id;
}

#endif
