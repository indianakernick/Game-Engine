//
//  graphics library.hpp
//  Game Engine
//
//  Created by Indi Kernick on 5/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_platform_interface_graphics_library_hpp
#define engine_platform_interface_graphics_library_hpp

#include "texture.hpp"
#include "shader.hpp"
#include "shader program.hpp"
#include "../../Memory/buffer.hpp"
#include "../../3D/texture params.hpp"
#include <glm/vec2.hpp>
#include <vector>

namespace Platform {
  Texture::Ptr makeTexture(Memory::Buffer,
                           glm::ivec2,
                           const Graphics3D::TexParams & = {});
  
  Shader::Ptr makeShader(Shader::Type, const Memory::Buffer);
  Shader::Ptr makeShader(Shader::Type, const Memory::Buffer, const Memory::Buffer);
  
  ShaderProgram::Ptr makeShaderProgram(const std::string &,
                                       const std::vector<Shader::Ptr> &);
}

#endif
