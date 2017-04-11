//
//  font loader.cpp
//  Game Engine
//
//  Created by Indi Kernick on 11/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "font loader.hpp"

#ifdef USE_OPENGL

using namespace Platform;

using Glyphs = std::vector<FT_Glyph>;
using Metrics = std::vector<GlyphMetrics>;
using GlyphPair = std::pair<Glyphs, Metrics>;
using Rects = std::vector<stbrp_rect>;
using Area = uint32_t;
using Length = uint16_t;
using TexData = std::vector<uint8_t>;
using Positions = std::vector<AtlasPos>;

namespace {
  FTHandle<FT_Library> freetype(FT_Done_FreeType);
  
  void initFreetype() {
    if (!freetype) {
      LOG_FT_ERROR(FT_Init_FreeType(&freetype));
    }
  }
  
  FTHandle<FT_Face> makeFace(Memory::Buffer buf, uint32_t size) {
    FTHandle<FT_Face> face(FT_Done_Face);
    LOG_FT_ERROR(FT_New_Memory_Face(freetype, buf.cdata<FT_Byte>(), buf.size<FT_Long>(), 0, &face));
    const glm::vec2 DPI = getDisplayDPI();
    LOG_FT_ERROR(FT_Set_Char_Size(face, 0, size * 64, DPI.x, DPI.y));
    if (!face->charmap) {
      throw FontLoadError("Font doesn't have Unicode support");
    }
    return face;
  }
  
  GlyphMetrics getMetrics(const FT_Glyph_Metrics &ftMetrics) {
    return {
      //bearing
      {
        Math::divRound(ftMetrics.horiBearingX, 64),
        Math::divRound(ftMetrics.horiBearingY, 64)
      },
      //size
      {
        Math::divRound(ftMetrics.width, 64),
        Math::divRound(ftMetrics.height, 64)
      },
      //advance
      static_cast<int32_t>(Math::divRound(ftMetrics.horiAdvance, 64))
    };
  }
  
  GlyphPair loadGlyphs(const FT_Face face, wchar_t firstChar, wchar_t numChars) {
    Glyphs glyphs(numChars);
    Metrics metrics(numChars);
    const wchar_t lastChar = firstChar + numChars;
    for (wchar_t c = firstChar; c != lastChar; c++) {
      static const FT_Int32 LOAD_FLAGS = FT_LOAD_DEFAULT
      #ifndef NDEBUG
      | FT_LOAD_PEDANTIC
      #endif
      ;
      LOG_FT_ERROR(FT_Load_Char(face, c, LOAD_FLAGS));
      metrics[c - firstChar] = getMetrics(face->glyph->metrics);
      LOG_FT_ERROR(FT_Get_Glyph(face->glyph, &glyphs[c - firstChar]));
    }
    return {glyphs, metrics};
  }
  
  Length calcLength(Area area) {
    const Length length = std::sqrt(std::ceil(area));
    const Length ceiledLength = Math::ceilToPowerOf2(length);
    if (static_cast<float>(length) / ceiledLength > 0.95f) {
      return ceiledLength * 2;
    } else {
      return ceiledLength;
    }
  }
  
  Rects packRects(const Metrics &metrics, Length &length) {
    Rects rects(metrics.size());
    Area area = 0;
    
    for (size_t i = 0; i != rects.size(); i++) {
      rects[i].id = static_cast<int>(i);
      rects[i].w = metrics[i].size.x;
      rects[i].h = metrics[i].size.y;
      area += rects[i].w * rects[i].h;
      rects[i].was_packed = false;
    }
    
    length = calcLength(area);
    const int lengthi = static_cast<int>(length);
    
    static std::vector<stbrp_node> nodes(1024);
    //the optimal number of nodes is equal to the width of the target
    if (length > nodes.size()) {
      nodes.resize(length);
    }
    
    stbrp_context context;
    stbrp_init_target(&context, lengthi, lengthi, nodes.data(), static_cast<int>(nodes.size()));
    stbrp_pack_rects(&context, rects.data(), static_cast<int>(rects.size()));
    
    #ifndef NDEBUG
    for (size_t i = 0; i != rects.size(); i++) {
      assert(rects[i].was_packed);
    }
    #endif
    
    return rects;
  }
  
  void copyBitmap(FT_Bitmap bitmap, uint8_t *data, Length pitch) {
    const uint8_t *bitmapData = bitmap.buffer;
    for (size_t y = 0; y != bitmap.rows; y++) {
      std::memcpy(data, bitmapData, bitmap.width);
      data += pitch;
      bitmapData += bitmap.pitch;
    }
  }
  
  TexData copyBitmaps(const Glyphs &glyphs, const Rects &rects, Length length) {
    std::vector<uint8_t> texData(length * length);
    for (size_t i = 0; i != rects.size(); i++) {
      const size_t glyphIndex = rects[i].id;
      FT_Glyph glyph = glyphs[glyphIndex];
      LOG_FT_ERROR(FT_Glyph_To_Bitmap(&glyph, FT_RENDER_MODE_NORMAL, nullptr, false));
      const FT_BitmapGlyph bitmap = reinterpret_cast<FT_BitmapGlyph>(glyph);
      const size_t pos = rects[i].y * length + rects[i].x;
      copyBitmap(bitmap->bitmap, texData.data() + pos, length);
    }
    return texData;
  }

  TextureImpl::Ptr makeTexture(const TexData &data, Length length) {
    GLuint id;
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 GL_RED,
                 length,
                 length,
                 0,
                 GL_RED,
                 GL_UNSIGNED_BYTE,
                 data.data());
    
    /*std::cout << "Size " << length << "\n\n";
    
    for (uint16_t y = 0; y < length; y++) {
      for (uint16_t x = 0; x < length; x++) {
        std::cout << " .:ioVM@"[data[y * length + x] >> 5];
      }
      std::cout << '\n';
    }
    std::cout << '\n';*/
    
    CHECK_OPENGL_ERROR();
    
    return std::make_shared<TextureImpl>(id);
  }

  Positions getPositions(const Rects &rects, Length length) {
    const float lengthf = length;
    Positions positions;
    positions.reserve(rects.size());
    for (size_t i = 0; i != positions.size(); ++i) {
      positions.push_back({
        //top left
        {
          rects[i].x / lengthf,
          rects[i].y / lengthf
        },
        //bottom right
        {
          (rects[i].x + rects[i].w) / lengthf,
          (rects[i].y + rects[i].h) / lengthf
        },
      });
    }
    return positions;
  }
}

Font::Ptr Platform::loadFont(
  Memory::Buffer buf,
  uint32_t size,
  wchar_t firstChar,
  wchar_t numChars
) {
  assert(numChars > 0);
  initFreetype();
  
  FontImpl::Ptr font = std::make_shared<FontImpl>();
  font->face = makeFace(buf, size);
  if (FT_HAS_FIXED_SIZES(font->face)) {
    throw FontLoadError("Font has embeded bitmaps");
  }
  
  font->fontMetrics.pointSize = size;
  font->fontMetrics.lineHeight = static_cast<uint32_t>(
    Math::divRound(font->face->size->metrics.height, 64)
  );
  
  Glyphs glyphs;
  //don't have structured bindings yet
  GlyphPair glyphPair = loadGlyphs(font->face, firstChar, numChars);
  glyphs.swap(glyphPair.first);
  font->metrics.swap(glyphPair.second);
  Length length;//packRects initializes length
  Rects rects = packRects(font->metrics, length);
  TexData texData = copyBitmaps(glyphs, rects, length);
  font->atlas = makeTexture(texData, length);
  font->positions = getPositions(rects, length);
  font->firstChar = firstChar;
  font->faceData.swap(buf);
  font->byteSize = font->metrics.size() * sizeof(GlyphMetrics) +
                   font->positions.size() * sizeof(AtlasPos) +
                   font->faceData.size() +
                   texData.size();
  
  return font;
}

#endif
