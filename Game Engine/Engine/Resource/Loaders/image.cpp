//
//  image.cpp
//  Game Engine
//
//  Created by Indi Kernick on 28/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "image.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../../../Libraries/stb_image.h"

const int Resource::Loaders::Image::BYTE_DEPTH = 4;

bool Resource::Loaders::Image::canLoad(const std::string &fileExt) {
  static const std::string EXT[] = {"jpg","jpeg","png","bmp","psd","tga","gif",
                                    "hdr","pic","pgm","ppm"};
  for (const std::string &ext : EXT) {
    if (fileExt == ext) {
      return true;
    }
  }
  return false;
}

size_t Resource::Loaders::Image::getSize(const Memory::Buffer file) {
  int x, y;
  stbi_info_from_memory(file.begin(), static_cast<int>(file.size()), &x, &y, nullptr);
  return x * y * BYTE_DEPTH;
}

bool Resource::Loaders::Image::useRaw() {
  return false;
}

Resource::Desc::Ptr Resource::Loaders::Image::process(const Memory::Buffer file, Memory::Buffer resource) {
  Geometry::Size size;
  Byte *temp = stbi_load_from_memory(file.begin(), static_cast<int>(file.size()), &size.w, &size.h, nullptr, BYTE_DEPTH);
  resource.copy(temp, size.area() * BYTE_DEPTH);
  stbi_image_free(temp);
  return std::make_shared<Descs::Image>(size, BYTE_DEPTH);
}
