//
//  element.cpp
//  Game Engine
//
//  Created by Indi Kernick on 1/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "element.hpp"

UI::AmbiguousID::AmbiguousID(const std::string &parent, const std::string &child)
  : std::runtime_error("Element \"" + parent + "\" already has an child with ID \"" + child + "\". Children must have unique IDs") {}

UI::BadID::BadID(const std::string &id)
  : std::runtime_error("The ID \"" + id + "\" is invalid") {}

UI::BadParentPtr::BadParentPtr(const std::string &message)
  : std::runtime_error(message) {}

UI::BadPolygon::BadPolygon()
  : std::runtime_error("A polygon must be empty or have more than two verticies") {}

UI::Texture::Texture(const std::string &path, const Trans2D &transform)
  : path(path), transform(transform) {}

UI::Element::Element(const std::string &id)
  : id(id) {
  if (!validID(id)) {
    throw BadID(id);
  }
}

void UI::Element::setBounds(const UI::AABB &newBounds) {
  bounds = newBounds;
}

const UI::AABB &UI::Element::getBounds() const {
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

void UI::Element::addChild(Element::Ptr child) {
  if (child->parent == this) {
    throw BadParentPtr("Cannot add the child \"" + child->id + "\" to the parent \"" + id + "\" more than once");
  }
  if (child->parent != nullptr) {
    throw BadParentPtr("Cannot add the child \"" + child->id + "\" to more than one parent");
  }
  for (auto c = children.cbegin(); c != children.cend(); c++) {
    if ((*c)->id == child->id) {
      throw AmbiguousID(id, child->id);
    }
  }
  children.push_front(child);
  child->parent = this;
}

void UI::Element::remChild(Element::Ptr child) {
  if (child->parent != this) {
    throw BadParentPtr("Cannot remove child \"" + child->id + "\" that is not a child of this element");
  }
  children.remove(child);
  child->parent = nullptr;
}

void UI::Element::remAllChildren() {
  children.remove_if([this](Element::Ptr child) {
    child->parent = nullptr;
    return true;
  });
}

const UI::Element::Children &UI::Element::getChildren() const {
  return children;
}

UI::Element::Ptr UI::Element::getChild(std::experimental::string_view childPath) const {
  const size_t nextIDPos = childPath.find_first_of('/') + 1;
  if (nextIDPos == 1) {
    throw BadID(childPath.to_string());
  }
  const std::experimental::string_view childID =
    nextIDPos == 0
    ? childPath
    : std::experimental::string_view(childPath.data(), nextIDPos)
  ;
  for (auto c = children.cbegin(); c != children.cend(); ++c) {
    if ((*c)->id == childID) {
      if (nextIDPos == 0) {
        return *c;
      } else {
        return (*c)->getChild({
          childPath.data() + nextIDPos,
          childPath.size() - nextIDPos - 1
        });
      }
    }
  }
  
  return nullptr;
}

UI::Element &UI::Element::getParent() const {
  if (parent == nullptr) {
    throw BadParentPtr("Tried to get the parent of \"" + id + "\" which doesn't have a parent");
  }
  return *parent;
}

bool UI::Element::hasParent() const {
  return parent;
}

bool UI::Element::validFirstIDChar(const char c) {
  return std::isalpha(c);
}

bool UI::Element::validIDChar(const char c) {
  return std::isalpha(c) || std::isdigit(c) || c == '_';
}

bool UI::Element::validID(const std::string &id) {
  return
    id.size() &&
    validFirstIDChar(id[0]) &&
    std::all_of(id.cbegin() + 1, id.cend(), validIDChar)
  ;
}
