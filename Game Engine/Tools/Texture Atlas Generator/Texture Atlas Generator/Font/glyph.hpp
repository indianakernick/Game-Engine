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
  std::vector<GlyphMetrics> metrics;
  std::vector<Image> images;
  wchar_t begin;
  wchar_t end;
};

#endif
