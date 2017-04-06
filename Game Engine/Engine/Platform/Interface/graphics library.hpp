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
#include "../../Memory/buffer.hpp"
#include "../../3D/texture params.hpp"
#include <glm/vec2.hpp>

namespace Platform {
  Texture::Ptr makeTexture(Memory::Buffer,
                           glm::ivec2,
                           const Graphics3D::TexParams & = {});
  
  Shader::Ptr makeShader(const Memory::Buffer, Shader::Type);
  Shader::Ptr makeShader(const Memory::Buffer, const Memory::Buffer, Shader::Type);
}

#endif
