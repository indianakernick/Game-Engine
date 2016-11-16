//
//  size.cpp
//  game engine
//
//  Created by Indi Kernick on 2/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "size.hpp"

Geometry::Size::Size(int w, int h)
  : w(w), h(h) {}

std::ostream &Geometry::operator<<(std::ostream &stream, Geometry::Size &size) {
  return stream << "Size {" << size.w << ", " << size.h << "}";
}

Geometry::Size Geometry::Size::operator+(const Size& other) const {
  return {w + other.w, h + other.h};
}

Geometry::Size Geometry::Size::operator-(const Size& other) const {
  return {w - other.w, h - other.h};
}

bool Geometry::Size::operator==(const Size& other) const {
  return w == other.w && h == other.h;
}

bool Geometry::Size::operator!=(const Size& other) const {
  return w != other.w || h != other.h;
}

template<>
Geometry::Size Math::lerp(double t, Geometry::Size from, Geometry::Size to) {
  return {
    Math::lerp(t, from.w, to.w),
    Math::lerp(t, from.h, to.h)
  };
}
