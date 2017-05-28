//
//  ui utils.cpp
//  Game Engine
//
//  Created by Indi Kernick on 1/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "aabb.hpp"

UI::BadBounds::BadBounds::BadBounds(const std::string &what)
  : std::runtime_error(what) {}

void UI::AABB::pos(const Point newPos) {
  mPos = newPos;
}

void UI::AABB::pos(const Coord newPos) {
  mPos.x = newPos;
  mPos.y = newPos;
}

void UI::AABB::thisOrigin(const UI::Origin newOrigin) {
  mThisOrigin = newOrigin;
}

void UI::AABB::parentOrigin(const UI::Origin newParentOrigin) {
  mParentOrigin = newParentOrigin;
}

void UI::AABB::bothOrigin(const UI::Origin newOrigin) {
  mThisOrigin = newOrigin;
  mParentOrigin = newOrigin;
}

void UI::AABB::posSpace(const Space newSpace) {
  mPosSpace = newSpace;
}

void UI::AABB::size(const Point newSize) {
  if (newSize.x < 0.0f && newSize.y < 0.0f) {
    throw BadBounds("Tried to set size to a negative value");
  }
  mSize = newSize;
}

void UI::AABB::size(const Coord newSize) {
  if (newSize < 0.0f) {
    throw BadBounds("Tried to set size to a negative value");
  }
  mSize = {newSize, newSize};
}

void UI::AABB::widthAndRatio(const Coord width, const Coord ratio) {
  if (width < 0.0f && ratio <= 0.0f) {
    throw BadBounds("Tried to set size to a negative value");
  }
  mSize.x = width;
  mSize.y = width / ratio;
}

void UI::AABB::heightAndRatio(const Coord height, const Coord ratio) {
  if (height < 0.0f && ratio <= 0.0f) {
    throw BadBounds("Tried to set size to a negative value");
  }
  mSize.x = height * ratio;
  mSize.y = height;
}

void UI::AABB::sizeSpace(const Space newSpace) {
  mSizeSpace = newSpace;
}

void UI::AABB::sizeAxis(const Axis newAxis) {
  mSizeAxis = newAxis;
}

void UI::AABB::space(const UI::Space newSpace) {
  mPosSpace = newSpace;
  mSizeSpace = newSpace;
}

UI::Point UI::AABB::pos() const {
  return mPos;
}

UI::Point UI::AABB::size() const {
  return mSize;
}

UI::Coord UI::AABB::width() const {
  return mSize.x;
}

UI::Coord UI::AABB::height() const {
  return mSize.y;
}

UI::Origin UI::AABB::thisOrigin() const {
  return mThisOrigin;
}

UI::Origin UI::AABB::parentOrigin() const {
  return mParentOrigin;
}

UI::Space UI::AABB::posSpace() const {
  return mPosSpace;
}

UI::Space UI::AABB::sizeSpace() const {
  return mSizeSpace;
}

UI::Axis UI::AABB::sizeAxis() const {
  return mSizeAxis;
}
