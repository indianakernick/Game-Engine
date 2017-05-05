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
    static_cast<int>(
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

//the squared distance between points
int distSquared(const ivec2 a, const ivec2 b) {
  return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}

Font loadFont(const std::string &path, const Font::Size &size) {
  std::cout << "Loading font \"" << path << "\"\n";
  
  initFreetype();
  FT_HANDLE(Face) face;
  CHECK_FT_ERROR(FT_New_Face(freetype, path.c_str(), 0, &face));
  CHECK_FT_ERROR(FT_Select_Charmap(face, FT_ENCODING_UNICODE));
  if (face->charmap == nullptr) {
    std::cout << "This font doesn't support unicode\n";
    if (face->num_charmaps == 0) {
      throw FontLoadError(path, "This font doesn't have any character maps");
    } else {
      CHECK_FT_ERROR(FT_Set_Charmap(face, face->charmaps[0]));
    }
  }
  if (face->num_fixed_sizes) {
    const ivec2 ppem = {
      (size.points * size.dpi.x / 72.0f) * 64.0f,
      (size.points * size.dpi.y / 72.0f) * 64.0f
    };
    size_t closestI = -1;
    int closestDist = -1;
    const size_t numSizes = face->num_fixed_sizes;
    for (size_t i = 0; i != numSizes; i++) {
      const ivec2 thisPPEM = {
        face->available_sizes[i].x_ppem,
        face->available_sizes[i].y_ppem
      };
      std::cout << thisPPEM.x / 64 << ", " << thisPPEM.y / 64 << '\n';
      const int distance = distSquared(ppem, thisPPEM);
      if (distance > closestDist) {
        closestDist = distance;
        closestI = i;
      }
    }
    CHECK_FT_ERROR(FT_Select_Size(face, static_cast<int>(closestI)));
  } else {
    CHECK_FT_ERROR(FT_Set_Char_Size(face, 0, size.points * 64, size.dpi.x, size.dpi.y));
  }
  Font font;
  font.size = size;
  font.metrics = getFontMetrics(face);
  font.face.swap(face);
  return font;
}
