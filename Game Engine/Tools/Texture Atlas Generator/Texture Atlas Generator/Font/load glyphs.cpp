//
//  load glyphs.cpp
//  Texture Atlas Generator
//
//  Created by Indi Kernick on 24/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "load glyphs.hpp"

#include "../math.hpp"
#include "freetype error.hpp"
#include FT_GLYPH_H
#include FT_BITMAP_H
#include <cstdlib>

GlyphMetrics getMetrics(const FT_Glyph_Metrics &metrics) {
  return {
    //bearing
    {
      divRound(metrics.horiBearingX, 64),
      divRound(metrics.horiBearingY, 64)
    },
    //size
    {
      divRound(metrics.width, 64),
      divRound(metrics.height, 64)
    },
    //advance
    static_cast<int>(divRound(metrics.horiAdvance, 64))
  };
}

FT_Error deleteGlyph(FT_Glyph glyph) {
  //FT_Done_Glyph doesn't return an error code. That's really annoying
  FT_Done_Glyph(glyph);
  return FT_Err_Ok;
}

#include <cassert>
#include <iostream>
#include "../Image/write image.hpp"

Glyphs loadGlyphs(const Font &font) {
  std::vector<GlyphMetrics> metrics;
  std::vector<Image> images;
  metrics.reserve(font.info.endChar - font.info.beginChar);
  images.reserve(font.info.endChar - font.info.beginChar);
  
  for (wchar_t c = font.info.beginChar; c != font.info.endChar; c++) {
    CHECK_FT_ERROR(FT_Load_Char(font.face, c, FT_LOAD_DEFAULT));
    
    metrics.push_back(getMetrics(font.face->glyph->metrics));
    
    FTHandle<FT_Glyph, deleteGlyph> glyph;
    CHECK_FT_ERROR(FT_Get_Glyph(font.face->glyph, &glyph));
    CHECK_FT_ERROR(FT_Glyph_To_Bitmap(&glyph, FT_RENDER_MODE_NORMAL, nullptr, true));
    FT_BitmapGlyph bitmapGlyph = glyph.as<FT_BitmapGlyph>();
    
    assert(static_cast<int>(bitmapGlyph->bitmap.width) == bitmapGlyph->bitmap.pitch);
    
    images.emplace_back(
      bitmapGlyph->bitmap.width,
      bitmapGlyph->bitmap.rows,
      Image::Format::GREY,
      bitmapGlyph->bitmap.buffer,
      &std::free
    );
    //Image takes ownership of the FT_Bitmap
    bitmapGlyph->bitmap.buffer = nullptr;
  }
  
  return {
    std::move(metrics),
    std::move(images),
    font.info.beginChar,
    font.info.endChar
  };
}
