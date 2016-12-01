//
//  id.cpp
//  Game Engine
//
//  Created by Indi Kernick on 26/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "id.hpp"

std::hash<std::string> Resource::ID::hasher;

Resource::ID::ID(std::string path)
  : path(path), hash(hasher(path)) {}

const std::string &Resource::ID::getPath() const {
  return path;
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
