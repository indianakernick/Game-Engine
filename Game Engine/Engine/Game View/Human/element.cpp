//
//  element.cpp
//  Game Engine
//
//  Created by Indi Kernick on 1/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "element.hpp"

UI::BadPolygon::BadPolygon()
  : std::runtime_error("A polygon must be empty or have more than two verticies") {}

UI::Texture::Texture(const std::string &path, const Trans2D &transform)
  : path(path), transform(transform) {}

UI::Element::Element(const std::string &id)
  : Node<Element>(id) {}

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
  if (newHitRegion.size() == 1 || newHitRegion.size() == 2) {
    throw BadPolygon();
  }
  hitRegion = newHitRegion;
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

void UI::Element::setTexture(const Texture &texture, const size_t index) {
  if (index < textures.size()) {
    textures[index] = texture;
  } else if (index == textures.size()) {
    textures.emplace_back(texture);
  } else {
    throw std::range_error("Texture index out of range");
  }
}

void UI::Element::setTexture(
  const std::string &path,
  const Trans2D &transform,
  const size_t index
) {
  if (index < textures.size()) {
    textures[index].path = path;
    textures[index].transform = transform;
  } else if (index == textures.size()) {
    textures.emplace_back(path, transform);
  } else {
    throw std::range_error("Texture index out of range");
  }
}

void UI::Element::appendTexture(const Texture &texture) {
  textures.emplace_back(texture);
}

void UI::Element::appendTexture(const std::string &path, const Trans2D &transform) {
  textures.emplace_back(path, transform);
}

void UI::Element::setTextures(const Textures &newTextures) {
  textures = newTextures;
}

const UI::Textures &UI::Element::getTextures() const {
  return textures;
}

UI::Element::ListenerID UI::Element::addEventListener(
  const Event::Type type,
  const Listener &listener
) {
  return dispatcher.addListenerAndCreateGroup(type, listener);
}

void UI::Element::remListener(const ListenerID listenerID) {
  dispatcher.remListener(listenerID);
}

void UI::Element::dispatchEvent(const Event::Type type, const Event::Ptr event) {
  assert(event);
  dispatcher.dispatch(type, event);
}
