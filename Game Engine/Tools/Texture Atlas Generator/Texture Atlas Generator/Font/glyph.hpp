//
//  glyph.hpp
//  Texture Atlas Generator
//
//  Created by Indi Kernick on 24/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef glyph_hpp
#define glyph_hpp

#include "../vector.hpp"
#include <vector>
#include "../Image/image.hpp"

struct GlyphMetrics {
  ivec2 bearing;
  ivec2 size;
  int advance;
};

struct Glyphs {
  Glyphs(const Glyphs &) = delete;
  Glyphs(Glyphs &&) = default;
  
  Glyphs &operator=(const Glyphs &) = delete;
  Glyphs &operator=(Glyphs &&) = default;

  std::vector<int> kerning;
  std::vector<GlyphMetrics> metrics;
  std::vector<Image> images;
  uint32_t begin;
  uint32_t end;
};

#endif
