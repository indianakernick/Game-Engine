//
//  render text.hpp
//  Game Engine
//
//  Created by Indi Kernick on 11/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_platform_opengl_render_text_hpp
#define engine_platform_opengl_render_text_hpp

#ifdef USE_OPENGL

#include "../Interface/render text.hpp"
#include "shader program.hpp"
#include "buffer.hpp"
#include "attribs.hpp"
#include "set uniform.hpp"
#include "type enum.hpp"
#include "texture.hpp"
#include "font.hpp"
#include <vector>

namespace Platform::RenderText {
  static constexpr size_t MAX_GLYPHS = 1000;

  class ContextImpl final : public Context {
  public:
    ContextImpl(Window::Ptr,
                ShaderProgramImpl::Ptr,
                VertexArray,
                ArrayBuffer,
                ArrayBuffer,
                ElementBuffer);
    ~ContextImpl() = default;
    
    AABB bounds(glm::ivec2, Font::Ptr, const std::wstring &) override;
    void render(glm::ivec2, Color, Font::Ptr, const std::wstring &) override;
  
  private:
    Window::Ptr window;
    ShaderProgramImpl::Ptr program;
    VertexArray vao;
    ArrayBuffer pos, tex;
    ElementBuffer elem;
    GLint windowSizeLoc, texLoc, colorLoc;
    std::unique_ptr<Pos2DType[]> posData;
    std::unique_ptr<TexType[]> texData;
    
    void assignPos(Pos2DType &, glm::ivec2);
    void assignTex(TexType &, glm::vec2);
    size_t setPosData(glm::ivec2, FontImpl::Ptr, const std::wstring &);
    size_t setTexData(FontImpl::Ptr, const std::wstring &);
  };
}

#endif

#endif
