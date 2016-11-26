//
//  id.cpp
//  Game Engine
//
//  Created by Indi Kernick on 26/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "id.hpp"

Resource::ID::ID(std::string path)
  : path(path) {}

const std::string &Resource::ID::getPath() const {
  return path;
}

bool Resource::ID::operator<(const ID &other) const {
  return path < other.path;
}

bool Resource::ID::operator==(const ID &other) const {
  return path == other.path;
}

bool Resource::ID::operator!=(const ID &other) const {
  return path != other.path;
}
