//
//  opengl font.hpp
//  Game Engine
//
//  Created by Indi Kernick on 26/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_handles_opengl_font_hpp
#define engine_resource_handles_opengl_font_hpp

#ifdef USE_OPENGL

#include "../handle.hpp"
#include "../../Application/opengl.hpp"
#include "../Loaders/freetype raii.hpp"
#include <glm/vec2.hpp>
#include <vector>
#include "../../Utils/combine.hpp"
#include FT_FREETYPE_H

namespace Res {
  struct FontInfo {
    uint32_t size;
    wchar_t firstChar = L' ';
    wchar_t numChars = L'~' - L' ';
    
    bool operator==(const FontInfo &) const;
    bool operator!=(const FontInfo &) const;
  };
  
  ///Metrics for a particular glyph
  struct GlyphMetrics {
    glm::tvec2<int32_t> bearing;
    glm::tvec2<uint32_t> size;
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

  class FontOpenGL final : public Handle {
  friend class FontLoaderOpenGL;
  public:
    using Ptr = std::shared_ptr<FontOpenGL>;
    
    FontOpenGL();
    ~FontOpenGL();
    
    GLuint getAtlas() const;
    FontMetrics getMetrics() const;
    bool hasKerning() const;
    int32_t getKerning(wchar_t, wchar_t) const;
    GlyphMetrics getMetrics(wchar_t) const;
    AtlasPos getPos(wchar_t) const;
  private:
    GLuint atlas;
    FTHandle<FT_Face> face;
    FontMetrics fontMetrics;
    std::vector<GlyphMetrics> metrics;
    std::vector<AtlasPos> positions;
    wchar_t firstChar;
    
    bool validChar(wchar_t) const;
  };
}

template <>
struct std::hash<Res::FontInfo> {
  size_t operator()(const Res::FontInfo &) const;
};

#endif

#endif
