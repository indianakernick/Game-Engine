//
//  opengl shader.hpp
//  Game Engine
//
//  Created by Indi Kernick on 8/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_loaders_opengl_shader_hpp
#define engine_resource_loaders_opengl_shader_hpp

#include "../loader.hpp"
#include "../Descriptions/opengl shader.hpp"
#include "../../Utils/logger.hpp"

namespace Resource {
  namespace Loaders {
    class ShaderOpenGL : public Loader {
    public:
      bool canLoad(const std::string &fileExt) override;
      size_t getSize(const Memory::Buffer file) override;
      bool useRaw() override;
      Desc::Ptr process(const Memory::Buffer, Memory::Buffer) override;
    private:
      bool vertShader = false;
    };
  }
}

#endif
