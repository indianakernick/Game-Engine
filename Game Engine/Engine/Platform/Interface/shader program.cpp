//
//  shader program.cpp
//  Game Engine
//
//  Created by Indi Kernick on 8/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "shader program.hpp"

using namespace Platform;

ShaderProgramLoadError::ShaderProgramLoadError(const char *what)
  : std::runtime_error(what) {}

ShaderProgram::ShaderProgram(const std::string &name)
  : name(name) {
  assert(name.size());
}

ShaderProgram::~ShaderProgram() {}

const std::string &ShaderProgram::getName() const {
  return name;
}
