//
//  shader.cpp
//  Game Engine
//
//  Created by Indi Kernick on 6/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "shader.hpp"

Platform::ShaderLoadError::ShaderLoadError(const char *what)
  : std::runtime_error(what) {}

Platform::Shader::Shader(Type type)
  : type(type) {}

Platform::Shader::Type Platform::Shader::getType() const {
  return type;
}
