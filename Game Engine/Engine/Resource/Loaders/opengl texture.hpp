//
//  opengl texture.hpp
//  Game Engine
//
//  Created by Indi Kernick on 17/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_loaders_opengl_texture_hpp
#define engine_resource_loaders_opengl_texture_hpp

//#include "../../Application/opengl.hpp"

#ifdef __gl_h_

#include "../loader.hpp"
#include "../Descriptions/opengl texture.hpp"
#include "../../../Libraries/stb_image.h"

namespace Resource {
  namespace Loaders {
    class TextureOpenGL : public Loader {
    public:
      bool canLoad(const std::string &fileExt) override;
      size_t getSize(const Memory::Buffer file) override;
      bool useRaw() override;
      Desc::Ptr process(const Memory::Buffer, Memory::Buffer) override;
    };
  }
}

#endif

#endif
