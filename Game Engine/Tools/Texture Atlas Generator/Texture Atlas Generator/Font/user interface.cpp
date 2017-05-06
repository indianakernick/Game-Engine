//
//  user interface.cpp
//  Texture Atlas Generator
//
//  Created by Indi Kernick on 3/5/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "user interface.hpp"

#include "load font.hpp"
#include "load glyphs.hpp"
#include "../math.hpp"
#include "../Image/pack images.hpp"
#include "../Image/make image.hpp"
#include "../Image/write image.hpp"
#include "write atlas.hpp"

void createFontAtlas(
  const std::string &input,
  const std::string &output,
  Font::Size fontSize,
  CodePoint begin,
  CodePoint end
) {
  const Font font = loadFont(input, fontSize);
  Glyphs glyphs = loadGlyphs(font, begin, end);
  const Length length = packImages(glyphs.images);
  writeImage(output + ".png", makeImage(glyphs.images, length));
  writeAtlas(output + ".atlas", font, glyphs, length);
}

#undef CHECK_NODE
