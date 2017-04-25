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

FTHandle<FT_Library, FT_Done_FreeType> freetype;

void initFreetype() {
  if (!freetype) {
    CHECK_FT_ERROR(FT_Init_FreeType(&freetype));
  }
}

Font loadFont(const std::string &path, const Font::Info &info) {
  std::cout << "Loading font \"" << path << "\"\n";
  
  initFreetype();
  FT_HANDLE(Face) face;
  CHECK_FT_ERROR(FT_New_Face(freetype, path.c_str(), 0, &face));
  if (face->charmap == nullptr) {
    std::cout << "This font doesn't support unicode\n";
    if (face->num_charmaps == 0) {
      std::cout << "This font doesn't have any character maps\n";
    } else {
      FT_Set_Charmap(face, face->charmaps[0]);
    }
  }
  CHECK_FT_ERROR(FT_Set_Char_Size(face, 0, info.pointSize * 64, info.dpi.x, info.dpi.y));
  Font font;
  font.info = info;
  font.face.swap(face);
  return font;
}
