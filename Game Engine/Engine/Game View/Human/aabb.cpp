//
//  ui utils.cpp
//  Game Engine
//
//  Created by Indi Kernick on 1/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "aabb.hpp"

void UI::AABB::setPos(const glm::vec2 newPos) {
  pos = newPos;
}

void UI::AABB::setPos(const float x, const float y) {
  pos.x = x;
  pos.y = y;
}

void UI::AABB::setPos(const float newPos) {
  pos.x = newPos;
  pos.y = newPos;
}

void UI::AABB::setThisOrigin(const UI::Origin newOrigin) {
  origin = newOrigin;
}

void UI::AABB::setParentOrigin(const UI::Origin newParentOrigin) {
  parentOrigin = newParentOrigin;
}

void UI::AABB::setBothOrigin(const UI::Origin newOrigin) {
  origin = newOrigin;
  parentOrigin = newOrigin;
}

void UI::AABB::setPosSpace(const Space space) {
  posSpace = space;
}

void UI::AABB::setSize(const glm::vec2 newSize) {
  assert(newSize.x > 0.0f && newSize.y > 0.0f);
  size = newSize;
}

void UI::AABB::setSize(const float w, const float h) {
  assert(w > 0.0f && h > 0.0f);
  size.x = w;
  size.y = h;
}

void UI::AABB::setSize(const float newSize) {
  assert(newSize > 0.0f);
  size = {newSize, newSize};
}

void UI::AABB::setSizeWidthRatio(const float width, const float ratio) {
  assert(width > 0.0f && ratio > 0.0f);
  size.x = width;
  size.y = size.x / ratio;
}

void UI::AABB::setSizeHeightRatio(const float height, const float ratio) {
  assert(height > 0.0f && ratio > 0.0f);
  size.y = height;
  size.x = size.y * ratio;
}

void UI::AABB::setSizeSpace(const Space space) {
  sizeSpace = space;
}

void UI::AABB::setSizeAxis(const Axis newAxis) {
  propAxis = newAxis;
}

void UI::AABB::setSpace(const UI::Space space) {
  posSpace = space;
  sizeSpace = space;
}
