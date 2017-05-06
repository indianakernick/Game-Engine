//
//  load glyphs.hpp
//  Texture Atlas Generator
//
//  Created by Indi Kernick on 24/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef load_glyphs_hpp
#define load_glyphs_hpp

#include "glyph.hpp"
#include "font.hpp"

class GlyphLoadError final : public std::runtime_error {
public:
  GlyphLoadError(CodePoint, const char *);
};

Glyphs loadGlyphs(const Font &, CodePoint, CodePoint);

#endif
