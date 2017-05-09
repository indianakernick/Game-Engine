//
//  user interface.cpp
//  Texture Atlas Generator
//
//  Created by Indi Kernick on 3/5/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "user interface.hpp"

#include "load font.hpp"
#include "load face.hpp"
#include "../Image/pack images.hpp"
#include "../Image/make image.hpp"
#include "../Image/write image.hpp"
#include "write atlas.hpp"
#include "../profiler.hpp"

void createFontAtlas(
  const std::string &input,
  const std::string &output,
  FaceSize size,
  CodePointRange range,
  SizePx sep
) {
  PROFILE(createFontAtlas);
  
  const Font font = loadFont(input);
  Face face = loadFace(font, size, range);
  const SizePx length = packImages(face.glyphs, sep);
  writeImage(output + ".png", makeImage(face.glyphs, length));
  writeAtlas(output + ".atlas", face, length);
}

#undef CHECK_NODE
