//
//  image.cpp
//  Texture Atlas Generator
//
//  Created by Indi Kernick on 22/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "image.hpp"

#include "memory.h"

Image::Image(int width, int height)
  : data(allocate<uint8_t>(width * height * 4), &deallocate),
    w(width),
    h(height) {}

Image::Image(int width, int height, uint8_t *data, const std::string &path)
  : data(data, &deallocate),
    path(path),
    w(width),
    h(height) {}
