//
//  render text.cpp
//  Game Engine
//
//  Created by Indi Kernick on 11/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "render text.hpp"

#ifdef USE_OPENGL

using namespace Platform;
using namespace Platform::RenderText;

ContextImpl::ContextImpl(Window::Ptr window,
                         ShaderProgramImpl::Ptr program,
                         VertexArray vao,
                         ArrayBuffer pos,
                         ArrayBuffer tex,
                         ElementBuffer elem)
  : window(window),
    program(program),
    vao(std::move(vao)),
    pos(std::move(pos)),
    tex(std::move(tex)),
    elem(std::move(elem)),
    windowSizeLoc(glGetUniformLocation(program->getID(), "windowSize")),
    texLoc(glGetUniformLocation(program->getID(), "tex")),
    colorLoc(glGetUniformLocation(program->getID(), "color")),
    posData(new Pos2DType[MAX_GLYPHS]),
    texData(new TexType[MAX_GLYPHS]) {
  assert(program);
  CHECK_OPENGL_ERROR();
}

AABB ContextImpl::bounds(glm::ivec2 origin, Font::Ptr font, const std::wstring &text) {
  AABB aabb;
  aabb.tl = origin;
  aabb.br = origin;
  FontImpl::Ptr fontImpl = std::dynamic_pointer_cast<FontImpl>(font);
  assert(fontImpl);
  glm::ivec2 pen = origin;
  wchar_t prevChar = '\0';
  for (auto c = text.cbegin(); c != text.cend(); ++c) {
    if (*c == '\n') {
      pen.x = origin.x;
      pen.y += fontImpl->fontMetrics.lineHeight;
    } else {
      const GlyphMetrics metrics = fontImpl->getMetrics(*c);
      pen.x += fontImpl->getKerning(prevChar, *c);
      aabb.tl.x = std::min(aabb.tl.x, pen.x + metrics.bearing.x);
      aabb.tl.y = std::min(aabb.tl.y, pen.y - metrics.bearing.y);
      aabb.br.x = std::max(aabb.br.x, pen.x + metrics.bearing.x + metrics.size.x);
      aabb.br.y = std::max(aabb.br.y, pen.y - metrics.bearing.y + metrics.size.y);
      pen.x += metrics.advance;
    }
    prevChar = *c;
  }
  return aabb;
}

void ContextImpl::render(
  glm::ivec2 origin,
  Color color,
  Font::Ptr font,
  const std::wstring &text
) {
  assert(text.size() <= MAX_GLYPHS);
  
  FontImpl::Ptr fontImpl = std::dynamic_pointer_cast<FontImpl>(font);
  assert(fontImpl);
  
  const size_t size = setPosData(origin, fontImpl, text);
  const size_t otherSize = setTexData(fontImpl, text);
  assert(size == otherSize);
  
  pos.bind();
  glBufferSubData(GL_ARRAY_BUFFER, 0, size * 4 * sizeof(Pos2DType), posData.get());
  tex.bind();
  glBufferSubData(GL_ARRAY_BUFFER, 0, size * 4 * sizeof(TexType), texData.get());
  
  vao.bind();
  program->bind();
  
  glDisable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  
  glBlendEquationSeparate(GL_FUNC_ADD, GL_FUNC_ADD);
  glBlendFuncSeparate(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
  
  //final.rgb = src.rgb * src.a + dst.rgb * (1 - src.a)
  //final.a = src.a * 1 + dst.a * (1 - src.a)
  
  setUniform(windowSizeLoc, glm::ivec2(window->size()));
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, fontImpl->atlas->getID());
  setUniform(texLoc, 0);
  setUniform(colorLoc, color);
  
  glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(6 * size), TypeEnum<ElemType>::type, 0);
}

void ContextImpl::assignPos(Pos2DType &dst, glm::ivec2 src) {
  dst[0] = src[0];
  dst[1] = src[1];
}

void ContextImpl::assignTex(TexType &dst, glm::vec2 src) {
  dst[0] = src[0];
  dst[1] = src[1];
}

size_t ContextImpl::setPosData(
  glm::ivec2 origin,
  FontImpl::Ptr font,
  const std::wstring &text
) {
  glm::ivec2 pen = origin;
  wchar_t prevChar = '\0';
  size_t i = 0;
  for (size_t c = 0; c != text.size(); c++) {
    if (text[c] == '\n') {
      pen.x = origin.x;
      pen.y = font->fontMetrics.lineHeight;
    }
    if (font->validChar(text[c])) {
      const GlyphMetrics metrics = font->getMetrics(text[c]);
      pen.x += font->getKerning(prevChar, text[c]);
      const glm::ivec2 tl = pen + metrics.bearing;
      assignPos(posData[i * 4 + 0], tl);//top-left
      assignPos(posData[i * 4 + 1], {tl.x + metrics.size.x, tl.y});//top-right
      assignPos(posData[i * 4 + 2], tl + metrics.size);//bottom-right
      assignPos(posData[i * 4 + 3], {tl.x, tl.y + metrics.size.y});//bottom-left
      pen.x += metrics.advance;
    } else {
      i--;
    }
    i++;
  }
  return i;
}

size_t ContextImpl::setTexData(FontImpl::Ptr font, const std::wstring &text) {
  size_t i = 0;
  for (size_t c = 0; c != text.size(); c++) {
    if (font->validChar(text[c])) {
      const AtlasPos pos = font->getPos(text[c]);
      assignTex(texData[c * 4 + 0], pos.tl);//top-left
      assignTex(texData[c * 4 + 1], {pos.br.x, pos.tl.y});//top-right
      assignTex(texData[c * 4 + 2], pos.br);//bottom-right
      assignTex(texData[c * 4 + 3], {pos.tl.x, pos.br.y});//bottom-left
    } else {
      i--;
    }
    i++;
  }
  return i;
}

namespace {
  ArrayBuffer makePosBuffer() {
    ArrayBuffer pos(BIND);
    
    glBufferData(GL_ARRAY_BUFFER, POS_2D_SIZE * 4 * MAX_GLYPHS, nullptr, GL_DYNAMIC_DRAW);
    enablePos2D();
    pos2DPointer(0, 0);
    CHECK_OPENGL_ERROR();
    
    return pos;
  }
  
  ArrayBuffer makeTexBuffer() {
    ArrayBuffer tex(BIND);
    
    glBufferData(GL_ARRAY_BUFFER, TEX_SIZE * 4 * MAX_GLYPHS, nullptr, GL_DYNAMIC_DRAW);
    enableTexturePos();
    texturePosPointer(0, 0);
    CHECK_OPENGL_ERROR();
    
    return tex;
  }
  
  ElementBuffer makeElemBuffer() {
    ElementBuffer elem(BIND);
    /*
    ┌───┐
    │╲  │
    │ ╲ │
    │  ╲│
    └───┘
    */
    static ElemType elemData[6 * MAX_GLYPHS];
    static bool elemDataInit = false;
    if (!elemDataInit) {
      const ElemType pattern[6] = {
        0, 3, 2, 0, 2, 1
      };
      for (size_t i = 0; i < 6 * MAX_GLYPHS; i++) {
        elemData[i] = pattern[i % 6];
      }
      elemDataInit = true;
    }
    
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, ELEM_SIZE * 6 * MAX_GLYPHS, elemData, GL_STATIC_DRAW);
    CHECK_OPENGL_ERROR();
    
    return elem;
  }
}

Context::Ptr Platform::RenderText::makeContext(
  Window::Ptr window,
  ShaderProgram::Ptr program
) {
  //the vao must be constructed before the makeBuffer functions are called
  //the order of evaluation of function parameters is unspecified
  VertexArray vao(BIND);
  
  return std::make_shared<ContextImpl>(
    window,
    std::dynamic_pointer_cast<ShaderProgramImpl>(program),
    std::move(vao),
    makePosBuffer(),
    makeTexBuffer(),
    makeElemBuffer()
  );
}

#endif
