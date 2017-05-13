//
//  user interface.cpp
//  Texture Atlas Generator
//
//  Created by Indi Kernick on 3/5/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "user interface.hpp"

#include "load images.hpp"
#include "../Utils/pack rects.hpp"
#include "blit images.hpp"
#include "write image.hpp"
#include "../Utils/search dir.hpp"
#include "write atlas.hpp"
#include "../Utils/profiler.hpp"
#include "rects from images.hpp"

void createImageAtlas(
  const std::string &input,
  const std::string &output,
  SizePx whitepixel,
  SizePx sep
) {
  PROFILE(createImageAtlas);

  std::remove((output + ".png").c_str());
  std::vector<Image> images = loadImages(findFiles(input, extIsImage));
  if (whitepixel != NO_WHITE_PIXEL) {
    const SizePx size = 1 + whitepixel * 2;
    images.emplace_back(size, size, images.back().format, 255);
  }
  std::vector<RectPx> rects = rectsFromImages(images);
  const SizePx length = packRects(rects, sep);
  writeImage(output + ".png", makeAndBlit(images, rects, length));
  writeAtlas(output + ".atlas", images, rects, length, whitepixel != NO_WHITE_PIXEL);
}
