//
//  opengl texture.hpp
//  Game Engine
//
//  Created by Indi Kernick on 17/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_loaders_opengl_texture_hpp
#define engine_resource_loaders_opengl_texture_hpp

#ifdef USE_OPENGL

#include "../loader.hpp"
#include "../Handles/opengl texture.hpp"
#include "../../../Libraries/stb_image.h"

namespace Res {
  class TextureLoaderOpenGL : public Loader {
  public:
    const std::string &getName() override;
    bool canLoad(const std::string &fileExt) override;
    Handle::Ptr load(const ID &id) override;
  };
}

#endif

#endif
