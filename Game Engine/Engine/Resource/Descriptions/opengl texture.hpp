//
//  opengl texture.hpp
//  Game Engine
//
//  Created by Indi Kernick on 17/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_descriptions_opengl_texture_hpp
#define engine_resource_descriptions_opengl_texture_hpp

#include "../../Application/opengl.hpp"

#ifdef __gl_h_

#include "../desc.hpp"

namespace Resource {
  namespace Descs {
    class TextureOpenGL : public Desc {
    public:
      using Ptr = std::shared_ptr<TextureOpenGL>;
      
      TextureOpenGL(GLuint textureID);
      ~TextureOpenGL();
      
      GLuint getID() const;
      
    private:
      GLuint textureID;
    };
  }
}

#endif

#endif
