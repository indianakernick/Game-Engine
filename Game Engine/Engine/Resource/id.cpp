//
//  id.cpp
//  Game Engine
//
//  Created by Indi Kernick on 26/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "id.hpp"

std::hash<std::string> Resource::ID::hasher;

Resource::ID::ID()
  : hash(0) {}

Resource::ID::ID(std::string path)
  : path(path), hash(hasher(path)) {}

Resource::ID::ID(const char *path)
  : path(path), hash(hasher(this->path)) {}

Resource::ID &Resource::ID::operator=(const std::string &newPath) {
  path = newPath;
  hash = hasher(path);
  return *this;
}

Resource::ID &Resource::ID::operator=(const char *newPath) {
  path = newPath;
  hash = hasher(path);
  return *this;
}

const std::string &Resource::ID::getPath() const {
  return path;
}

bool Resource::ID::isNull() const {
  return hash == 0;
}

bool Resource::ID::operator<(const ID &other) const {
  return hash < other.hash;
}

bool Resource::ID::operator==(const ID &other) const {
  return hash == other.hash;
}

bool Resource::ID::operator!=(const ID &other) const {
  return hash != other.hash;
}
