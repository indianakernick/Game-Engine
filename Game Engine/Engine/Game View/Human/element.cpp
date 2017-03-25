//
//  element.cpp
//  Game Engine
//
//  Created by Indi Kernick on 1/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "element.hpp"

void UI::Element::setBounds(const UI::AABB &newBounds) {
  bounds = newBounds;
}

const UI::AABB &UI::Element::getBounds() const {
  return bounds;
}

UI::AABB &UI::Element::getBounds() {
  return bounds;
}

void UI::Element::setHitRegion(const Polygon &newHitRegion) {
  hitRegion = newHitRegion;
  assert(hitRegion.size() != 1 && hitRegion.size() != 2);
}

void UI::Element::unsetHitRegion() {
  hitRegion.clear();
}

const UI::Polygon &UI::Element::getHitRegion() const {
  return hitRegion;
}

bool UI::Element::hasHitRegion() const {
  return hitRegion.size();
}

void UI::Element::setHeight(Height newHeight) {
  height = newHeight;
}

UI::Height UI::Element::getHeight() const {
  return height;
}

void UI::Element::setPassthrough(bool newPassthrough) {
  passthrough = newPassthrough;
}

bool UI::Element::getPassthrough() const {
  return passthrough;
}

void UI::Element::setColor(const Color &newColor) {
  color = newColor;
}

const UI::Color &UI::Element::getColor() const {
  return color;
}

UI::Color &UI::Element::getColor() {
  return color;
}

void UI::Element::addChild(Element::Ptr child) {
  assert(child->parent != this);
  assert(child->parent == nullptr);
  children.push_front(child);
  child->parent = this;
}

void UI::Element::remChild(Element::Ptr child) {
  assert(child->parent == this);
  children.remove(child);
  child->parent = nullptr;
}

void UI::Element::remAllChildren() {
  children.remove_if([this](Element::Ptr child) {
    assert(child->parent == this);
    child->parent = nullptr;
    return true;
  });
}

const UI::Element::Children &UI::Element::getChildren() const {
  return children;
}

UI::Element &UI::Element::getParent() const {
  assert(parent);
  return *parent;
}

bool UI::Element::hasParent() const {
  return parent;
}
