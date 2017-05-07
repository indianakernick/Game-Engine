//
//  load font.cpp
//  Texture Atlas Generator
//
//  Created by Indi Kernick on 24/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "load font.hpp"

#include "freetype error.hpp"
#include <iostream>
#include "../math.hpp"
#include "../profiler.hpp"

FontLoadError::FontLoadError(const std::string &file, const char *reason)
  : std::runtime_error("Failed to load font \"" + file + "\": " + reason) {}

FTHandle<FT_Library, FT_Done_FreeType> freetype;

void initFreetype() {
  if (!freetype) {
    CHECK_FT_ERROR(FT_Init_FreeType(&freetype));
  }
}

Font::Metrics getFontMetrics(const FT_HANDLE(Face) &face) {
  return {
    //lineHeight
    static_cast<unsigned>(
      divRound(
        face->size->metrics.height,
        64
      )
    ),
    //minY
    static_cast<int>(
      divRound(
        FT_MulFix(face->bbox.yMin, face->size->metrics.y_scale),
        64
      )
    ),
    //maxY
    static_cast<int>(
      divRound(
        FT_MulFix(face->bbox.yMax, face->size->metrics.y_scale),
        64
      )
    )
  };
}

Font loadFont(const std::string &path, const Font::Size &size) {
  PROFILE(loadFont);

  std::cout << "Loading font \"" << path << "\"\n";
  
  initFreetype();
  FT_HANDLE(Face) face;
  CHECK_FT_ERROR(FT_New_Face(freetype, path.c_str(), 0, &face));
  CHECK_FT_ERROR(FT_Set_Char_Size(face, 0, size.points * 64, size.dpi.x, size.dpi.y));
  Font font;
  font.size = size;
  font.metrics = getFontMetrics(face);
  font.face.swap(face);
  return font;
}
