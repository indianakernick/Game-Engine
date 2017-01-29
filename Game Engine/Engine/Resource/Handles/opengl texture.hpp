//
//  opengl texture.hpp
//  Game Engine
//
//  Created by Indi Kernick on 17/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_handles_opengl_texture_hpp
#define engine_resource_handles_opengl_texture_hpp

#ifdef USE_OPENGL

#include "../../Application/opengl.hpp"
#include "../handle.hpp"

namespace Res {
  class TextureOpenGL : public Handle {
  public:
    using Ptr = std::shared_ptr<TextureOpenGL>;
    
    TextureOpenGL(GLuint textureID);
    ~TextureOpenGL();
    
    GLuint getID() const;
  private:
    GLuint textureID;
  };
}

#endif

#endif
