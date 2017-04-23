//
//  image.cpp
//  Texture Atlas Generator
//
//  Created by Indi Kernick on 22/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "image.hpp"

Image::Image(int width, int height)
  : data(new uint8_t[width * height * 4]), w(width), h(height) {}

Image::Image(int width, int height, uint8_t *data, const std::string &path)
  : data(data), path(path), w(width), h(height) {}
