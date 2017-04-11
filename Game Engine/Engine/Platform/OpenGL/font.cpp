//
//  font.cpp
//  Game Engine
//
//  Created by Indi Kernick on 11/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "font.hpp"

#ifdef USE_OPENGL

using namespace Platform;

FontImpl::FontImpl()
  : face(FT_Done_Face), faceData(0) {}

FontImpl::~FontImpl() {
  face.del();
  //face must be deleted before faceData is deleted
}

size_t FontImpl::getByteSize() const {
  return byteSize;
}

bool FontImpl::hasKerning() const {
  return FT_HAS_KERNING(face);
}

int32_t FontImpl::getKerning(wchar_t left, wchar_t right) const {
  if (FT_HAS_KERNING(face)) {
    const FT_UInt leftIndex = FT_Get_Char_Index(face, left);
    const FT_UInt rightIndex = FT_Get_Char_Index(face, right);
    FT_Vector kerning;
    //FT_Get_Kerning returns (0, 0) when an error occurs so there's no need to
    //check the error code
    FT_Get_Kerning(face, leftIndex, rightIndex, FT_KERNING_DEFAULT, &kerning);
    return static_cast<int32_t>(Math::divRound(kerning.x, 64));
  } else {
    return 0;
  }
}

GlyphMetrics FontImpl::getMetrics(wchar_t c) const {
  assert(validChar(c));
  return metrics[c - firstChar];
}

AtlasPos FontImpl::getPos(wchar_t c) const {
  assert(validChar(c));
  return positions[c - firstChar];
}

bool FontImpl::validChar(wchar_t c) const {
  return static_cast<size_t>(c - firstChar) < metrics.size();
}

#endif
