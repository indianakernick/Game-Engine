//
//  pack images.cpp
//  Texture Atlas Generator
//
//  Created by Indi Kernick on 22/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "pack images.hpp"

#include <cmath>
#include <iostream>
#include "../math.hpp"
#include "../Libraries/stb_rect_pack.h"

ImagePackError::ImagePackError(const std::string &path)
  : std::runtime_error("Failed to pack image \"" + path + "\"") {}

Length calcArea(const std::vector<Image> &images) {
  Length area = 0;
  for (auto i = images.cbegin(); i != images.cend(); i++) {
    area += i->s.x * i->s.y;
  }
  return area;
}

Length calcLength(Length area) {
  const Length length = std::ceil(std::sqrt(area));
  const Length ceiledLength = ceilToPowerOf2(length);
  if (static_cast<float>(length) / ceiledLength > 0.85f) {
    return ceiledLength * 2;
  } else {
    return ceiledLength;
  }
}

std::vector<stbrp_rect> fillRects(const std::vector<Image> &images) {
  std::vector<stbrp_rect> rects(images.size());
  
  for (size_t i = 0; i != images.size(); i++) {
    rects[i].id = static_cast<int>(i);
    rects[i].w = images[i].s.x + 1;
    rects[i].h = images[i].s.y + 1;
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

std::vector<stbrp_rect> packRects(Length length, const std::vector<Image> &images) {
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

Length packImages(std::vector<Image> &images) {
  std::cout << "Packing images\n";
  
  const Length length = calcLength(calcArea(images));
  std::vector<stbrp_rect> rects = packRects(length, images);
  
  for (size_t i = 0; i != images.size(); i++) {
    images[i].p.x = rects[i].x;
    images[i].p.y = rects[i].y;
  }
  
  return length;
}
