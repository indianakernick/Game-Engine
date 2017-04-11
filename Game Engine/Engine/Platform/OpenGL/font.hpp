//
//  font.hpp
//  Game Engine
//
//  Created by Indi Kernick on 11/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_platform_opengl_font_hpp
#define engine_platform_opengl_font_hpp

#ifdef USE_OPENGL

#include "../Interface/font.hpp"
#include "texture.hpp"
#include "freetype raii.hpp"
#include FT_FREETYPE_H
#include <glm/vec2.hpp>
#include <vector>
#include "../../Math/round.hpp"
#include "../../Memory/buffer.hpp"
#include "../Interface/font loader.hpp"

namespace Platform {
  ///Metrics for a particular glyph
  struct GlyphMetrics {
    glm::ivec2 bearing;
    glm::ivec2 size;
    int32_t advance;
  };
  
  ///Metrics for an entire font face
  struct FontMetrics {
    uint32_t pointSize;
    uint32_t lineHeight;
  };
  
  ///Normalized texture coordinates of a glyph on the atlas
  struct AtlasPos {
    //Top-left
    glm::vec2 tl;
    //Bottom-right
    glm::vec2 br;
  };

  class FontImpl final : public Font {
  friend Font::Ptr Platform::loadFont(Memory::Buffer, uint32_t, wchar_t, wchar_t);
  public:
    using Ptr = std::shared_ptr<FontImpl>;
  
    FontImpl();
    ~FontImpl();
    
    size_t getByteSize() const override;
    
    bool hasKerning() const;
    int32_t getKerning(wchar_t, wchar_t) const;
    GlyphMetrics getMetrics(wchar_t) const;
    AtlasPos getPos(wchar_t) const;
    
    TextureImpl::Ptr atlas;
    FTHandle<FT_Face> face;
    Memory::Buffer faceData;
    FontMetrics fontMetrics;
    std::vector<GlyphMetrics> metrics;
    std::vector<AtlasPos> positions;
    wchar_t firstChar;
    size_t byteSize;
    
    bool validChar(wchar_t) const;
  };
}

#endif

#endif
