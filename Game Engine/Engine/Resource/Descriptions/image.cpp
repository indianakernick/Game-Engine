//
//  image.cpp
//  Game Engine
//
//  Created by Indi Kernick on 30/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "image.hpp"

Resource::Descs::Image::Image(Geometry::Size size, int depth)
  : size(size), depth(depth) {}

Geometry::Size Resource::Descs::Image::getSize() {
  return size;
}

int Resource::Descs::Image::getDepth() {
  return depth;
}
