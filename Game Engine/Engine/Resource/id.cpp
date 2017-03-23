//
//  id.cpp
//  Game Engine
//
//  Created by Indi Kernick on 26/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "id.hpp"

Res::ID::ID()
  : hash(0) {}

Res::ID::ID(const std::string &path)
  : path(path) {
  init();
}

Res::ID::ID(std::string &&path)
  : path(path) {
  init();
}

Res::ID::ID(const char *path)
  : path(path) {
  init();
}

Res::ID::ID(const std::string &path, Any data)
  : path(path), data(data) {
  init();
}

Res::ID::ID(std::string &&path, Any data)
  : path(path), data(data) {
  init();
}

Res::ID::ID(const char *path, Any data)
  : path(path), data(data) {
  init();
}

Res::ID &Res::ID::operator=(const std::string &newPath) {
  path = newPath;
  init();
  return *this;
}

Res::ID &Res::ID::operator=(std::string &&newPath) {
  path = newPath;
  init();
  return *this;
}

Res::ID &Res::ID::operator=(const char *newPath) {
  path = newPath;
  init();
  return *this;
}

Res::ID::operator bool() const {
  return hash;
}

const std::string &Res::ID::getPath() const {
  return path;
}

const char *Res::ID::getPathC() const {
  return path.c_str();
}

std::experimental::string_view Res::ID::getExt() const {
  return {path.c_str() + path.find_last_of('.')};
}

std::experimental::string_view Res::ID::getEnclosingFolder() const {
  const size_t lastSlash = path.find_last_of('/');
  if (lastSlash == std::string::npos) {
    return {};
  } else {
    return {path.data(), lastSlash + 1};
  }
}

std::experimental::string_view Res::ID::getName() const {
  const size_t lastSlash = path.find_last_of('/');
  //npos + 1 = 0
  //x - npos = x + 1
  return {path.data() + (lastSlash + 1), path.find_last_of('.') - lastSlash - 1};
}

std::experimental::string_view Res::ID::getNameExt() const {
  return {path.c_str() + path.find_last_of('/') + 1};
}

const Any &Res::ID::getData() const {
  return data;
}

bool Res::ID::operator==(const ID &other) const {
  return hash == other.hash;
}

bool Res::ID::operator!=(const ID &other) const {
  return hash != other.hash;
}

void Res::ID::init() {
  validatePath();
  createHash();
}

void Res::ID::validatePath() {
  #ifndef NDEBUG
  if (path.find_last_of('/') == path.size() - 1) {
    LOG_ERROR(RESOURCES, "Res::ID path \"%s\" is a folder", path.c_str());
    return;
  }
  
  const size_t lastDot = path.find_last_of('.');
  
  if (lastDot == std::string::npos || lastDot == path.size() - 1) {
    LOG_ERROR(RESOURCES, "Res::ID path \"%s\" doesn't have an extension", path.c_str());
    return;
  }
  
  for (size_t i = lastDot + 1; i != path.size(); i++) {
    if (!islower(path[i]) && !isnumber(path[i])) {
      LOG_ERROR(RESOURCES,
        "Res::ID extension \"%s\" can only contain lower case alphabet characters and numbers",
        path.c_str());
      return;
    }
  }
  #endif
}

void Res::ID::createHash() {
  hash = hashCombine(path, data);
}

size_t std::hash<Res::ID>::operator()(const Res::ID &id) const {
  return id.hash;
}
