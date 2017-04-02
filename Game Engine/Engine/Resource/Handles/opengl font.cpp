//
//  opengl font.cpp
//  Game Engine
//
//  Created by Indi Kernick on 26/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "opengl font.hpp"

#ifdef USE_OPENGL

bool Res::FontInfo::operator==(const FontInfo &other) const {
  return size == other.size &&
         firstChar == other.firstChar &&
         numChars == other.numChars;
}

bool Res::FontInfo::operator!=(const FontInfo &other) const {
  return !(*this == other);
}

Res::FontOpenGL::FontOpenGL()
  : face(FT_Done_Face) {}

Res::FontOpenGL::~FontOpenGL() {
  glDeleteTextures(1, &atlas);
}

GLuint Res::FontOpenGL::getAtlas() const {
  return atlas;
}

Res::FontMetrics Res::FontOpenGL::getMetrics() const {
  return fontMetrics;
}

int32_t Res::FontOpenGL::getKerning(wchar_t left, wchar_t right) {
  if (hasKerning) {
    const FT_UInt leftIndex = FT_Get_Char_Index(face, left);
    const FT_UInt rightIndex = FT_Get_Char_Index(face, right);
    FT_Vector kerning;
    FT_Get_Kerning(face, leftIndex, rightIndex, FT_KERNING_DEFAULT, &kerning);
    return static_cast<int32_t>(Math::divRound(kerning.x, 64));
  } else {
    return 0;
  }
}

Res::GlyphMetrics Res::FontOpenGL::getMetrics(wchar_t c) const {
  assert(validChar(c));
  return metrics[c - firstChar];
}

Res::AtlasPos Res::FontOpenGL::getPos(wchar_t c) const {
  assert(validChar(c));
  return positions[c - firstChar];
}

bool Res::FontOpenGL::validChar(wchar_t c) const {
  return static_cast<size_t>(c - firstChar) < metrics.size();
}


size_t std::hash<Res::FontInfo>::operator()(const Res::FontInfo &info) const {
  return hashCombine(info.size, info.firstChar, info.numChars);
}

#endif
