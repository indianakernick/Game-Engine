//
//  conversions.cpp
//  Game Engine
//
//  Created by Indi Kernick on 30/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "conversions.hpp"

UI::PointPx UI::toPixels(const Point point, const PointPx scale) {
  return {
    point.x * scale.x,
    point.y * scale.y
  };
}

UI::BoundsPx UI::toPixels(const Bounds bounds, const PointPx scale) {
  return bounds.convertMul<int>(scale);
}

UI::TexCoordsPx UI::toPixels(const TexCoords texCoords, const PointPx scale) {
  return texCoords.convertMul<int>(scale);
}

UI::Point UI::fromPixels(const PointPx point, const PointPx scale) {
  return {
    static_cast<float>(point.x) / scale.x,
    static_cast<float>(point.y) / scale.y
  };
}

UI::Bounds UI::fromPixels(const BoundsPx bounds, const PointPx scale) {
  return bounds.convertDiv<float>(scale);
}

UI::TexCoords UI::fromPixels(const TexCoordsPx texCoords, const PointPx scale) {
  return texCoords.convertDiv<float>(scale);
}
