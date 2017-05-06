//
//  make image.cpp
//  Texture Atlas Generator
//
//  Created by Indi Kernick on 23/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "make image.hpp"

#include <iostream>
#include <cassert>

void copyImageTo(Image &dst, const Image &src) {
  assert(dst.format == src.format);
  
  uint8_t *dstPtr = dst.data.get();
  const uint8_t *srcPtr = src.data.get();
  const uintptr_t format = src.format;
  
  for (int y = 0; y != src.s.y; y++) {
    std::memcpy(
      dstPtr + ((y + src.p.y) * dst.s.x + src.p.x) * format,
      srcPtr + (y * src.s.x) * format,
      src.s.x * format
    );
  }
}

Image makeImage(const std::vector<Image> &images, Length length) {
  assert(images.size());
  
  std::cout << "Copying smaller images onto larger image\n";

  Image image(length, length, images[0].format);
  std::memset(image.data.get(), 0, image.s.x * image.s.y * image.format);
  
  for (auto i = images.cbegin(); i != images.cend(); i++) {
    copyImageTo(image, *i);
  }
  
  return image;
}
