//
//  opengl font.hpp
//  Game Engine
//
//  Created by Indi Kernick on 26/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_loaders_opengl_font_hpp
#define engine_resource_loaders_opengl_font_hpp

#ifdef USE_OPENGL

#include "../loader.hpp"
#include "../Handles/opengl font.hpp"
#include "../../Platform/Interface/window library.hpp"
#include "../../../Libraries/stb_rect_pack.h"
#include FT_GLYPH_H
#include "../../Math/round.hpp"

namespace Res {
  class FontLoaderOpenGL final : public Loader {
  public:
    const std::string &getName() const override;
    bool canLoad(std::experimental::string_view ext) const override;
    Handle::Ptr load(const ID &id) const override;
  
  private:
    static FTHandle<FT_Library> freetype;
    
    using Glyphs = std::vector<FT_Glyph>;
    using Metrics = std::vector<GlyphMetrics>;
    using GlyphPair = std::pair<Glyphs, Metrics>;
    using Rects = std::vector<stbrp_rect>;
    using Area = uint32_t;
    using Length = uint16_t;
    using TexData = std::vector<uint8_t>;
    using Positions = std::vector<AtlasPos>;
    
    static void initFreetype();
    static FTHandle<FT_Face> makeFace(const char *, uint32_t);
    static GlyphMetrics getMetrics(const FT_Glyph_Metrics &);
    static GlyphPair loadGlyphs(FT_Face, wchar_t, wchar_t);
    static Length calcLength(Area);
    static Rects packRects(const Metrics &, Length &);
    static TexData copyBitmaps(const Glyphs &, const Rects &, Length);
    static void copyBitmap(FT_Bitmap, uint8_t *, Length);
    static GLuint makeTexture(const TexData &, Length);
    static Positions getPositions(const Rects &, Length);
  };
}

#endif

#endif
