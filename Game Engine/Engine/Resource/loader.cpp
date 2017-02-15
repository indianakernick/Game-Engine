//
//  loader.cpp
//  Game Engine
//
//  Created by Indi Kernick on 10/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "loader.hpp"

Res::FileError::FileError(const char *what)
  : std::runtime_error(what) {}

std::string Res::Loader::absPath(const ID &id) {
  return path() + id.getPath();
}

std::ifstream Res::Loader::openFileStream(const ID &id) {
  std::ifstream stream(absPath(id), std::ios::binary);
  if (!stream.is_open()) {
    throw FileError("Failed to open file stream");
  }
  return stream;
}

std::FILE *Res::Loader::openFile(const ID &id) {
  std::FILE *file = std::fopen(absPath(id).c_str(), "rb");
  if (file == nullptr) {
    throw FileError("Failed to open file");
  }
  return file;
}

Memory::Buffer Res::Loader::readFile(const ID &id) {
  std::FILE *file = openFile(id);
  
  std::fseek(file, 0, SEEK_END);
  Memory::Buffer buffer(std::ftell(file));
  std::rewind(file);
  if (std::fread(buffer.begin(), buffer.size(), 1, file)) {
    std::fclose(file);
    return buffer;
  } else {
    std::fclose(file);
    throw FileError("Failed to read file");
  }
}

bool Res::Loader::hasExt(const std::vector<std::string> &exts,
                         const std::string &ext) {
  return std::any_of(exts.cbegin(), exts.cend(), [&ext](const std::string &thisExt) {
    return ext == thisExt;
  });
}
