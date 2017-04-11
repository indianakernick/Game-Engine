//
//  font.cpp
//  Game Engine
//
//  Created by Indi Kernick on 11/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "font.hpp"

bool Res::NewFontInfo::operator==(const NewFontInfo &other) const {
  return size == other.size &&
         firstChar == other.firstChar &&
         numChars == other.numChars;
}

bool Res::NewFontInfo::operator!=(const NewFontInfo &other) const {
  return !(*this == other);
}

Res::Font::Font(Platform::Font::Ptr font)
  : font(font) {
  assert(font);
}

Platform::Font::Ptr Res::Font::getFont() const {
  return font;
}

size_t std::hash<Res::NewFontInfo>::operator()(const Res::NewFontInfo &info) const {
  return hashCombine(info.size, info.firstChar, info.numChars);
}
