//
//  make image.cpp
//  Texture Atlas Generator
//
//  Created by Indi Kernick on 23/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "make image.hpp"

#include <iostream>

FormatError::FormatError()
  : std::runtime_error("Cannot construct image from images of different formats") {}

void copyImageTo(Image &dst, const Image &src) {
  uint8_t *dstPtr = dst.data.get();
  const uint8_t *srcPtr = src.data.get();
  const uintptr_t format = src.format;
  
  for (unsigned y = 0; y != src.s.y; y++) {
    std::memcpy(
      dstPtr + ((y + src.p.y) * dst.s.x + src.p.x) * format,
      srcPtr + (y * src.s.x) * format,
      src.s.x * format
    );
  }
}

Image makeImage(const std::vector<Image> &images, Length length) {
  std::cout << "Copying smaller images onto larger image\n";
  
  for (auto i = images.cbegin(); i != images.cend(); i++) {
    if (i->format != images.front().format) {
      throw FormatError();
    }
  }

  const Image::Format format = images.size() ? images.front().format : Image::Format::GREY;
  Image image(length, length, format);
  std::memset(image.data.get(), 0, image.s.x * image.s.y * image.format);
  
  for (auto i = images.cbegin(); i != images.cend(); i++) {
    copyImageTo(image, *i);
  }
  
  return image;
}
