//
//  opengl shader.hpp
//  Game Engine
//
//  Created by Indi Kernick on 8/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_loaders_opengl_shader_hpp
#define engine_resource_loaders_opengl_shader_hpp

#ifdef USE_OPENGL

#include "../loader.hpp"
#include "../Handles/opengl shader.hpp"
#include "../../Utils/logger.hpp"

namespace Res {
  class ShaderLoaderOpenGL : public Loader {
  public:
    const std::string &getName() override;
    bool canLoad(const std::string &fileExt) override;
    Handle::Ptr load(const ID &id) override;
  private:
    bool vertShader = false;
  };
}

#endif

#endif
