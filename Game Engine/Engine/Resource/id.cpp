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

Resource::ID::ID(std::nullptr_t)
  : hash(0) {}

Resource::ID::ID(std::string path)
  : path(path), hash(hasher(path)) {
  createExt();
}

Resource::ID::ID(const char *path)
  : path(path), hash(hasher(this->path)) {
  createExt();
}

Resource::ID &Resource::ID::operator=(const std::string &newPath) {
  path = newPath;
  createExt();
  hash = hasher(path);
  return *this;
}

Resource::ID &Resource::ID::operator=(const char *newPath) {
  path = newPath;
  createExt();
  hash = hasher(path);
  return *this;
}

Resource::ID::operator bool() const {
  return hash;
}

const std::string &Resource::ID::getPath() const {
  return path;
}

const std::string &Resource::ID::getExt() const {
  return ext;
}

const char *Resource::ID::getPathC() const {
  return path.c_str();
}

const char *Resource::ID::getExtC() const {
  return ext.c_str();
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

void Resource::ID::createExt() {
  const int end = static_cast<int>(path.size());
  int lastDot = end;
  for (int i = end - 1; i >= 0; i--) {
    if (path[i] == '.') {
      lastDot = i;
      break;
    }
  }
  const int extSize = end - lastDot - 1;
  if (extSize < 1) {
    ext = "";
  } else {
    for (int i = 0; i < extSize; i++) {
      ext.push_back(tolower(path[i + lastDot + 1]));
    }
  }
}
