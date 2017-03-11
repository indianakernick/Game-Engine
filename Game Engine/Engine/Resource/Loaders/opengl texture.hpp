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
#include "../../3D/texture params.hpp"

namespace Res {
  class TextureLoaderOpenGL : public Loader {
  public:
    const std::string &getName() const override;
    bool canLoad(const std::string &ext) const override;
    Handle::Ptr load(const ID &id) const override;
  
  private:
    static void setTexParams(const Graphics3D::TexParams);
  };
}

#endif

#endif
