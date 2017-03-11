//
//  texture params.cpp
//  Game Engine
//
//  Created by Indi Kernick on 11/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "texture params.hpp"

using namespace Graphics3D;

void TexParams::disableAF() {
  af = AF_DISABLED;
}

bool TexParams::afEnabled() const {
  return af > AF_DISABLED;
}

void TexParams::setWrap(const TexWrap wrap) {
  wrapS = wrap;
  wrapT = wrap;
}

bool TexParams::operator==(const TexParams &other) const {
  return border == other.border &&
         wrapS == other.wrapS &&
         wrapT == other.wrapT &&
         min == other.min &&
         mag == other.mag &&
         af == other.af &&
         invert == other.invert &&
         hasAlpha == other.hasAlpha;
}

bool TexParams::operator!=(const TexParams &other) const {
  return !(*this == other);
}

size_t std::hash<glm::vec4>::operator()(const glm::vec4 &v) const {
  return hashCombine(v.x, v.y, v.z, v.w);
}

size_t std::hash<TexParams>::operator()(const TexParams &p) const {
  return hashCombine(p.border, p.wrapS, p.wrapT, p.min, p.mag,
                     p.af, p.invert, p.hasAlpha);
}
