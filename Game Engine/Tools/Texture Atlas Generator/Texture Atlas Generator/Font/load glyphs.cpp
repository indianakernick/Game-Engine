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

using namespace std::literals;

GlyphLoadError::GlyphLoadError(uint32_t c, const char *what)
  : std::runtime_error("Error loading glyph " + std::to_string(c) + ": " + what) {}

std::vector<int> getKerning(const FT_HANDLE(Face) &face, uint32_t beginChar, uint32_t endChar) {
  if (!FT_HAS_KERNING(face)) {
    std::cout << "Font doesn't support kerning\n";
    return {};
  }
  std::cout << "Reading kerning data\n";
  
  std::vector<int> kerning;
  const uint32_t numChars = endChar - beginChar;
  kerning.reserve(numChars * numChars);
  
  for (uint32_t l = beginChar; l != endChar; l++) {
    for (uint32_t r = beginChar; r != endChar; r++) {
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

union Pixel {
  uint8_t p[4];
  uint32_t data;
};

Pixel convertPixel(const Pixel in) {
  //input  BGRA pre-multiplied srgb
  //output RGBA srgb
  
  float r = in.p[2] / 255.0f;
  float g = in.p[1] / 255.0f;
  float b = in.p[0] / 255.0f;
  const float a = in.p[3] / 255.0f;
  r /= a;
  g /= a;
  b /= a;
  
  return {{
    static_cast<uint8_t>(r * 255.0f),
    static_cast<uint8_t>(g * 255.0f),
    static_cast<uint8_t>(b * 255.0f),
    in.p[3]
  }};
}

class BitmapConvertError {
public:
  BitmapConvertError(const char *what)
    : what(what) {}
  const char *what;
};

Image::Format convertFormat(FT_Pixel_Mode format) {
  switch (format) {
    case FT_PIXEL_MODE_GRAY:
      return Image::Format::GREY;
    case FT_PIXEL_MODE_MONO:
    case FT_PIXEL_MODE_GRAY2:
    case FT_PIXEL_MODE_GRAY4:
      throw BitmapConvertError("Subbyte bitmap formats are not supported");
    case FT_PIXEL_MODE_LCD:
    case FT_PIXEL_MODE_LCD_V:
      throw BitmapConvertError("LCD bitmap formats are not supported");
    case FT_PIXEL_MODE_BGRA:
      return Image::Format::RGB_ALPHA;
    default:
      assert(false);
  }
}

Image convertBitmap(FT_Bitmap &bitmap) {
  //this function might need rewriting. I kinda smells funny
  
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
    const uintptr_t width = bitmap.width, height = bitmap.rows;
    const Image::Format format = convertFormat(static_cast<FT_Pixel_Mode>(bitmap.pixel_mode));
    const uintptr_t depth = static_cast<uintptr_t>(format);
    const ptrdiff_t srcPitch = bitmap.pitch, dstPitch = width * depth;
    
    Image image(bitmap.width, bitmap.rows, format);
    
    const uint8_t *srcRow = bitmap.buffer;
    uint8_t *dstRow = image.data.get();
    for (uintptr_t y = 0; y != height; y++) {
      for (uintptr_t x = 0; x != width; x++) {
        const Pixel *srcPx = reinterpret_cast<const Pixel *>(srcRow + x * depth);
        Pixel *dstPx = reinterpret_cast<Pixel *>(dstRow + x * depth);
        *dstPx = convertPixel(*srcPx);
      }
      srcRow += srcPitch;
      dstRow += dstPitch;
    }
    
    return image;
  }
}

Glyphs loadGlyphs(const Font &font, uint32_t begin, uint32_t end) {
  std::cout << "Rendering glyphs\n";

  std::vector<GlyphMetrics> metrics;
  std::vector<Image> images;
  metrics.reserve(end - begin);
  images.reserve(end - begin);
  
  for (uint32_t c = begin; c != end; c++) {
    CHECK_FT_ERROR(FT_Load_Char(font.face, c, FT_LOAD_COLOR | FT_LOAD_RENDER));

    if (font.face->glyph->format != FT_GLYPH_FORMAT_BITMAP) {
      throw GlyphLoadError(c, "Glyph is in unknown format or was not able to be rendered");
    }

    metrics.push_back(getMetrics(font.face->glyph->metrics));
    try {
      Image image = convertBitmap(font.face->glyph->bitmap);
      if (images.size()) {
        if (images.back().format != image.format) {
          throw GlyphLoadError(c, "The pixel format of this glyph differs from the previous. Color emoji must be in separate ranges");
        }
      }
      images.emplace_back(std::move(image));
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
