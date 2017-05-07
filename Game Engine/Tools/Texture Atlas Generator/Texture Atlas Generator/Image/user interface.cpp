//
//  user interface.cpp
//  Texture Atlas Generator
//
//  Created by Indi Kernick on 3/5/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "user interface.hpp"

#include "load images.hpp"
#include "pack images.hpp"
#include "make image.hpp"
#include "write image.hpp"
#include "../search dir.hpp"
#include "write atlas.hpp"
#include "../profiler.hpp"

void createImageAtlas(
  const std::string &input,
  const std::string &output,
  int whitepixel,
  unsigned sep
) {
  PROFILE(createImageAtlas);

  std::remove((output + ".png").c_str());
  std::vector<Image> images = loadImages(findFiles(input));
  if (whitepixel >= 0) {
    const unsigned size = 1 + whitepixel * 2;
    images.emplace_back(size, size, images.back().format);
    std::memset(images.back().data.get(), 255, size * size * images.back().format);
  }
  const Length length = packImages(images, sep);
  writeImage(output + ".png", makeImage(images, length));
  writeAtlas(output + ".atlas", images, length, whitepixel >= 0);
}
