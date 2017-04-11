//
//  render 2d.hpp
//  Game Engine
//
//  Created by Indi Kernick on 8/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_platform_opengl_render_2d_hpp
#define engine_platform_opengl_render_2d_hpp

#ifdef USE_OPENGL

#include "../Interface/render 2d.hpp"
#include "shader program.hpp"
#include "buffer.hpp"
#include "attribs.hpp"
#include "set uniform.hpp"
#include "type enum.hpp"
#include <vector>
#include "texture.hpp"

namespace Platform::Render2D {
  class ListImpl final : public List {
  public:
    using Ptr = std::shared_ptr<ListImpl>;
  
    ListImpl() = default;
    ~ListImpl() = default;
    
    void push(Texture::Ptr, Color, Height, Bounds) override;
    void zsort() override;
    void clear() override;
  
    struct Object {
      TextureImpl::Ptr texture;
      Color color;
      Height height;
      Pos2DType bounds[4];
    };
    
    std::vector<Object> objects;
  };

  class ContextImpl final : public Context {
  public:
    ContextImpl(ShaderProgramImpl::Ptr,
                VertexArray,
                ArrayBuffer,
                ArrayBuffer,
                ElementBuffer);
    ~ContextImpl() = default;
    
    void render(const List::Ptr) override;
  
  private:
    ShaderProgramImpl::Ptr program;
    VertexArray vao;
    ArrayBuffer pos, tex;
    ElementBuffer elem;
    GLint texLoc, colorLoc;
  };
}

#endif

#endif
