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

void createImageAtlas(const std::string &input, const std::string &output) {
  std::remove((output + ".png").c_str());
  std::vector<Image> images = loadImages(findFiles(input));
  const Length length = packImages(images);
  writeAtlas(output + ".atlas", images, length);
  writeImage(output + ".png", makeImage(images, length));
}
