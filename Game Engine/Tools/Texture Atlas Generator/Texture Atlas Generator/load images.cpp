//
//  load images.cpp
//  Texture Atlas Generator
//
//  Created by Indi Kernick on 22/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "load images.hpp"

#define STB_MALLOC(size) (new uint8_t[size])
#define STB_FREE(ptr) (delete [] (ptr))
#define STB_REALLOC(ptr, size) (delete [] (ptr), new uint8_t [size])
#include "Libraries/stb_image.h"
#include <iostream>

ImageLoadError::ImageLoadError(const std::string &file, const std::string &reason)
  : std::runtime_error("Failed to load image: \"" + file + "\": " + reason) {}

NoLoadedImagesError::NoLoadedImagesError()
  : std::runtime_error("No images successfully loaded") {}

Image loadImage(const std::string &file) {
  std::cout << "Loading image \"" << file << "\"\n";

  int width, height;
  uint8_t *data = stbi_load(file.c_str(), &width, &height, nullptr, 4);
  if (data == nullptr) {
    throw ImageLoadError(file, stbi_failure_reason());
  }
  
  return {width, height, data, file};
}

std::vector<Image> loadImages(const std::vector<std::string> &files) {
  std::vector<Image> images;
  
  for (auto f = files.begin(); f != files.end(); f++) {
    try {
      images.emplace_back(loadImage(*f));
    } catch (ImageLoadError &e) {
      std::cerr << e.what() << '\n';
    }
  }
  
  if (images.size() == 0) {
    throw NoLoadedImagesError();
  }
  
  return images;
}
