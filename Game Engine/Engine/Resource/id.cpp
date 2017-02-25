//
//  id.cpp
//  Game Engine
//
//  Created by Indi Kernick on 26/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "id.hpp"

std::hash<std::string> Res::ID::strHasher;
std::hash<Any> Res::ID::anyHasher;

Res::ID::ID()
  : hash(0) {}

Res::ID::ID(std::nullptr_t)
  : hash(0) {}

Res::ID::ID(std::string path)
  : path(path) {
  init();
}

Res::ID::ID(const char *path)
  : path(path), hash(strHasher(this->path)) {
  init();
}

Res::ID::ID(std::string path, Any data)
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

const std::string &Res::ID::getExt() const {
  return ext;
}

std::string Res::ID::getEnclosingFolder() const {
  const size_t lastSlash = path.find_last_of('/');
  if (lastSlash == std::string::npos) {
    return "";
  } else {
    return path.substr(0, lastSlash + 1);
  }
}

std::string Res::ID::getName() const {
  const size_t lastSlash = path.find_last_of('/');
  //if lastSlash is npos then adding 1 will make it 0
  //subtracting npos adds 1
  return path.substr(lastSlash + 1, path.size() - ext.size() - 2 - lastSlash);
}

std::string Res::ID::getNameExt() const {
  return path.substr(path.find_last_of('/') + 1);
}

const Any &Res::ID::getData() const {
  return data;
}

const char *Res::ID::getPathC() const {
  return path.c_str();
}

const char *Res::ID::getExtC() const {
  return ext.c_str();
}

bool Res::ID::operator==(const ID &other) const {
  return hash == other.hash;
}

bool Res::ID::operator!=(const ID &other) const {
  return hash != other.hash;
}

void Res::ID::init() {
  validatePath();
  createExt();
  createHash();
}

void Res::ID::validatePath() {
  if (path.find_last_of('/') == path.size() - 1) {
    LOG_ERROR(RESOURCES, "Res::ID path \"%s\" is a folder", path.c_str());
  }
}

void Res::ID::createExt() {
  const size_t lastDot = path.find_last_of('.');
  if (lastDot == std::string::npos || lastDot == path.size() - 1) {
    LOG_ERROR(RESOURCES,
      "Res::ID path \"%s\" doesn't have an extension", path.c_str());
    ext = "";
  } else {
    const size_t extSize = (path.size() - 1) - lastDot;
    for (size_t i = 0; i < extSize; i++) {
      ext.push_back(tolower(path[i + lastDot + 1]));
    }
  }
}

void Res::ID::createHash() {
  //there's no std::hash_combine so here's boost::hash_combine
  const size_t strHash = strHasher(path);
  hash = strHash ^ (anyHasher(data) + 0x9e3779b9 + (strHash << 6) + (strHash >> 2));
}

size_t std::hash<Res::ID>::operator()(const Res::ID &id) const {
  return id.hash;
}

bool std::equal_to<Res::ID>::operator()(const Res::ID &a,
                                        const Res::ID &b) const {
  return a.hash == b.hash;
}
