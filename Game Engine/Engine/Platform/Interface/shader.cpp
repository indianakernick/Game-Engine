//
//  shader.cpp
//  Game Engine
//
//  Created by Indi Kernick on 6/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "shader.hpp"

using namespace Platform;

ShaderLoadError::ShaderLoadError(const char *what)
  : std::runtime_error(what) {}

Shader::Shader(Type type)
  : type(type) {}

Shader::~Shader() {}

Shader::Type Shader::getType() const {
  return type;
}
