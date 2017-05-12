//
//  make image.cpp
//  Texture Atlas Generator
//
//  Created by Indi Kernick on 23/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "make image.hpp"

#include <cassert>
#include <iostream>
#include "../Utils/profiler.hpp"

FormatError::FormatError()
  : std::runtime_error("Cannot construct image from images of different formats") {}

// Arial ASCII 1000pt
//   this 26.87ms
//   prev 75.95ms
//   this is 182% faster than prev
void copyImageTo(Image &dst, const Image &src, const PosPx2 srcPos) {
  PROFILE(copyImageTo);

  const ptrdiff_t dstPitch = dst.s.x * dst.format;
  const ptrdiff_t srcPitch = src.s.x * src.format;
  const size_t width = srcPitch;
  uint8_t *dstRow = dst.data.get() + srcPos.y * dstPitch + srcPos.x * src.format;
  const uint8_t *srcRow = src.data.get();
  
  for (SizePx y = 0; y != src.s.y; y++) {
    std::memcpy(dstRow, srcRow, width);
    dstRow += dstPitch;
    srcRow += srcPitch;
  }
}

Image makeImage(const std::vector<Image> &images, const std::vector<RectPx> &rects, SizePx length) {
  PROFILE(makeImage);

  std::cout << "Copying smaller images onto larger image\n";
  
  for (auto i = images.cbegin(); i != images.cend(); i++) {
    if (i->format != images.front().format) {
      throw FormatError();
    }
  }
  
  assert(images.size() == rects.size());

  const Image::Format format = images.size() ? images.front().format : Image::Format::GREY;
  Image image(length, length, format);
  std::memset(image.data.get(), 0, image.s.x * image.s.y * image.format);
  
  for (size_t i = 0; i != images.size(); i++) {
    copyImageTo(image, images[i], rects[i].p);
  }
  
  return image;
}
