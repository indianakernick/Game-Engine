//
//  shader.cpp
//  Game Engine
//
//  Created by Indi Kernick on 6/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "shader.hpp"

Res::Shader::Shader(Platform::Shader::Ptr shader)
  : shader(shader) {
  assert(shader);
}

Platform::Shader::Ptr Res::Shader::getShader() const {
  return shader;
}
