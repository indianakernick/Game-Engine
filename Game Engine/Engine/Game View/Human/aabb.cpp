//
//  ui utils.cpp
//  Game Engine
//
//  Created by Indi Kernick on 1/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "aabb.hpp"

void UI::AABB::setPos(glm::vec2 newPos) {
  pos = newPos;
}

void UI::AABB::setOrigin(Origin newOrigin, Origin newParentOrigin) {
  origin = newOrigin;
  parentOrigin = newParentOrigin;
}

void UI::AABB::setOrigin(Origin newOrigin) {
  origin = newOrigin;
  parentOrigin = newOrigin;
}

void UI::AABB::setPosSpace(Space space) {
  posSpace = space;
}

void UI::AABB::setSize(glm::vec2 newSize) {
  size = newSize;
  assert(size.x > 0.0f && size.y > 0.0f);
}

void UI::AABB::setSize(float newSize) {
  size = {newSize, newSize};
  assert(size.x > 0.0f && size.y > 0.0f);
}

void UI::AABB::setAspectRatio(float aspect) {
  aspectRatio = aspect;
  assert(aspectRatio > 0.0f);
}

void UI::AABB::setWidth(float width) {
  size.x = width;
  assert(size.x > 0.0f);
  size.y = size.x / aspectRatio;
}

void UI::AABB::setHeight(float height) {
  size.y = height;
  assert(size.y > 0.0f);
  size.x = size.y * aspectRatio;
}

void UI::AABB::setSizeSpace(Space space) {
  sizeSpace = space;
}

void UI::AABB::setSizeAxis(Axis newAxis) {
  propAxis = newAxis;
}

void UI::AABB::setSpace(UI::Space space) {
  posSpace = space;
  sizeSpace = space;
}
