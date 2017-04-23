//
//  write image.cpp
//  Texture Atlas Generator
//
//  Created by Indi Kernick on 22/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "write image.hpp"

#include "Libraries/stb_image_write.h"
#include <iostream>

ImageWriteError::ImageWriteError()
  : std::runtime_error("Failed to write image to file") {}

void writeImage(const std::string &file, const Image &image) {
  std::cout << "Writing image to file \"" << file << "\"\n";
  
  if (!stbi_write_png(file.c_str(), image.w, image.h, 4, image.data.get(), 0)) {
    throw ImageWriteError();
  }
}
