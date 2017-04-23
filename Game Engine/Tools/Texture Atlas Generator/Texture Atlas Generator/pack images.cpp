//
//  pack images.cpp
//  Texture Atlas Generator
//
//  Created by Indi Kernick on 22/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "pack images.hpp"

#include <cmath>
#include <cassert>
#include "Libraries/stb_rect_pack.h"
#include <iostream>

ImagePackError::ImagePackError(const std::string &path)
  : std::runtime_error("Failed to pack image \"" + path + "\"") {}

int calcArea(const std::vector<Image> &images) {
  int area = 0;
  for (auto i = images.cbegin(); i != images.cend(); i++) {
    area += i->w * i->h;
  }
  return area;
}

int ceilToPowerOf2(int num) {
  return (1 << (32 - __builtin_clz(num - 1))) - (num == 1);
}

int calcLength(int area) {
  const int length = std::ceil(std::sqrt(area));
  const int ceiledLength = ceilToPowerOf2(length);
  if (static_cast<float>(length) / ceiledLength > 0.95f) {
    return ceiledLength * 2;
  } else {
    return ceiledLength;
  }
}

std::vector<stbrp_rect> fillRects(const std::vector<Image> &images) {
  std::vector<stbrp_rect> rects(images.size());
  
  for (size_t i = 0; i != images.size(); i++) {
    rects[i].id = static_cast<int>(i);
    rects[i].w = images[i].w;
    rects[i].h = images[i].h;
    rects[i].was_packed = 0;
  }
  
  return rects;
}

class InternalImagePackError {
public:
  InternalImagePackError(size_t i)
    : i(i) {}
  
  size_t i;
};

void checkAllRectsPacked(const std::vector<stbrp_rect> &rects) {
  for (size_t r = 0; r != rects.size(); r++) {
    if (rects[r].was_packed == 0) {
      throw InternalImagePackError(r);
    }
  }
}

std::vector<stbrp_rect> packRects(int length, const std::vector<Image> &images) {
  std::vector<stbrp_node> nodes(length);
  std::vector<stbrp_rect> rects = fillRects(images);
  
  stbrp_context ctx;
  stbrp_init_target(&ctx, length, length, nodes.data(), static_cast<int>(nodes.size()));
  stbrp_pack_rects(&ctx, rects.data(), static_cast<int>(rects.size()));
  
  try {
    checkAllRectsPacked(rects);
  } catch (InternalImagePackError &e) {
    throw ImagePackError(images[e.i].path);
  }
  
  return rects;
}

int packImages(std::vector<Image> &images) {
  std::cout << "Packing images\n";
  
  const int length = calcLength(calcArea(images));
  std::vector<stbrp_rect> rects = packRects(length, images);
  
  for (size_t i = 0; i != images.size(); i++) {
    images[i].x = rects[i].x;
    images[i].y = rects[i].y;
  }
  
  return length;
}
