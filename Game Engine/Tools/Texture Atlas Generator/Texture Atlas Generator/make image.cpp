//
//  make image.cpp
//  Texture Atlas Generator
//
//  Created by Indi Kernick on 23/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "make image.hpp"

#include <iostream>

void copyImageTo(Image &dst, const Image &src) {
  uint8_t *dstPtr = dst.data.get();
  const uint8_t *srcPtr = src.data.get();
  
  for (int y = 0; y != src.h; y++) {
    std::memcpy(
      dstPtr + ((y + src.y) * dst.w + src.x) * 4,
      srcPtr + (y * src.w) * 4,
      src.w * 4
    );
  }
}

Image makeImage(const std::vector<Image> &images, int length) {
  std::cout << "Copying smaller images onto larger image\n";

  Image image(length, length);
  
  for (auto i = images.cbegin(); i != images.cend(); i++) {
    copyImageTo(image, *i);
  }
  
  return image;
}
