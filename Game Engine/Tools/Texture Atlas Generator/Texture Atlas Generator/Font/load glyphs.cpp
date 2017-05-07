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
#include <cstdlib>
#include <iostream>
#include <cassert>
#include "../profiler.hpp"

using namespace std::literals;

GlyphLoadError::GlyphLoadError(CodePoint c, const char *what)
  : std::runtime_error("Error loading glyph " + std::to_string(c) + ": " + what) {}

std::vector<int> getKerning(const FT_HANDLE(Face) &face, CodePoint beginChar, CodePoint endChar) {
  PROFILE(getKerning);
  
  if (!FT_HAS_KERNING(face)) {
    std::cout << "Font doesn't support kerning\n";
    return {};
  }
  std::cout << "Reading kerning data\n";
  
  std::vector<int> kerning;
  const CodePoint numChars = endChar - beginChar;
  kerning.reserve(numChars * numChars);
  
  for (CodePoint l = beginChar; l != endChar; l++) {
    for (CodePoint r = beginChar; r != endChar; r++) {
      FT_Vector kernVec;
      FT_Get_Kerning(
        face,
        FT_Get_Char_Index(face, l),
        FT_Get_Char_Index(face, r),
        FT_KERNING_DEFAULT,
        &kernVec
      );
      kerning.push_back(static_cast<int>(divRound(kernVec.x, 64)));
    }
  }
  
  return kerning;
}

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

class BitmapConvertError {
public:
  BitmapConvertError(const char *what)
    : what(what) {}
  const char *what;
};

Image convertBitmap(FT_Bitmap &bitmap) {
  if (bitmap.pixel_mode == FT_PIXEL_MODE_GRAY) {
    assert(static_cast<int>(bitmap.width) == bitmap.pitch);
    
    Image image(
      bitmap.width,
      bitmap.rows,
      Image::Format::GREY,
      bitmap.buffer,
      std::free
    );
    //Image takes ownership of the FT_Bitmap
    bitmap.buffer = nullptr;
    
    return image;
  } else {
    throw BitmapConvertError("Glyph is in unsupported format");
  }
}

Glyphs loadGlyphs(const Font &font, CodePoint begin, CodePoint end) {
  PROFILE(loadGlyphs);
  
  std::cout << "Rendering glyphs\n";

  std::vector<GlyphMetrics> metrics;
  std::vector<Image> images;
  metrics.reserve(end - begin);
  images.reserve(end - begin);
  
  for (char c = begin; c != end; c++) {
    CHECK_FT_ERROR(FT_Load_Char(font.face, c, FT_LOAD_RENDER));

    if (font.face->glyph->format != FT_GLYPH_FORMAT_BITMAP) {
      throw GlyphLoadError(c, "Glyph is in unsupported format");
    }

    metrics.push_back(getMetrics(font.face->glyph->metrics));
    try {
      images.push_back(convertBitmap(font.face->glyph->bitmap));
    } catch (BitmapConvertError &e) {
      throw GlyphLoadError(c, e.what);
    }
  }
  
  return {
    getKerning(font.face, begin, end),
    std::move(metrics),
    std::move(images),
    begin,
    end
  };
}
