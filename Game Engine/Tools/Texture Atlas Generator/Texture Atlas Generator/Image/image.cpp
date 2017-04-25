//
//  image.cpp
//  Texture Atlas Generator
//
//  Created by Indi Kernick on 22/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "image.hpp"

#include "memory.h"

Image::Image()
  : data(nullptr, [](auto){}) {}

Image::Image(int width, int height, Format format)
  : data(allocate<uint8_t>(width * height * static_cast<int>(format)), &deallocate),
    s(width, height),
    format(format) {}

Image::Image(int width, int height, Format format, uint8_t *data, void (*deleter)(void *))
  : data(data, deleter),
    s(width, height),
    format(format) {}

Image::Image(int width, int height, Format format, uint8_t *data, const std::string &path)
  : data(data, &deallocate),
    path(path),
    s(width, height),
    format(format) {}
