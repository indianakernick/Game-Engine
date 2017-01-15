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

std::string Resource::ID::getEnclosingFolder() const {
  size_t lastSlash = path.find_last_of('/');
  if (lastSlash == std::string::npos) {
    return "";
  } else if (lastSlash == path.size() - 1) {
    LOG_ERROR(RESOURCES, "Resource::ID path \"%s\" is a folder", path.c_str());
    return path;
  } else {
    return path.substr(0, lastSlash + 1);
  }
}

const char *Resource::ID::getPathC() const {
  return path.c_str();
}

const char *Resource::ID::getExtC() const {
  return ext.c_str();
}

bool Resource::ID::operator==(const ID &other) const {
  return hash == other.hash;
}

bool Resource::ID::operator!=(const ID &other) const {
  return hash != other.hash;
}

void Resource::ID::createExt() {
  const size_t lastDot = path.find_last_of('.');
  if (lastDot == std::string::npos || lastDot == path.size() - 1) {
    LOG_ERROR(RESOURCES,
      "Resource::ID path \"%s\" doesn't have an extension", path.c_str());
    ext = "";
  } else {
    const size_t extSize = path.size() - lastDot;
    for (size_t i = 0; i < extSize; i++) {
      ext.push_back(tolower(path[i + lastDot + 1]));
    }
  }
}

size_t std::hash<Resource::ID>::operator()(const Resource::ID &id) const {
  return id.hash;
}

bool std::equal_to<Resource::ID>::operator()(const Resource::ID &a,
                                             const Resource::ID &b) const {
  return a.hash == b.hash;
}
