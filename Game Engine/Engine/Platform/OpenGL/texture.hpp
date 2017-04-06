//
//  texture.hpp
//  Game Engine
//
//  Created by Indi Kernick on 5/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_platform_opengl_texture_hpp
#define engine_platform_opengl_texture_hpp

#ifdef USE_OPENGL

#include "../Interface/texture.hpp"
#include "opengl.hpp"
#include <cassert>

namespace Platform {
  class TextureImpl final : public Texture {
  public:
    TextureImpl(GLuint);
    ~TextureImpl();
    
    GLuint getID() const;
  private:
    GLuint id;
  };
}

#endif

#endif
