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

Res::Loader::FileHandle Res::Loader::openFile(const ID &id) {
  std::FILE *file = std::fopen(absPath(id).c_str(), "rb");
  if (file == nullptr) {
    throw FileError("Failed to open file");
  }
  return FileHandle(file, &std::fclose);
}

Memory::Buffer Res::Loader::readFile(const ID &id) {
  FileHandle file = openFile(id);
  
  std::fseek(file.get(), 0, SEEK_END);
  Memory::Buffer buffer(std::ftell(file.get()));
  std::rewind(file.get());
  if (std::fread(buffer.begin(), buffer.size(), 1, file.get())) {
    return buffer;
  } else {
    throw FileError("Failed to read file");
  }
}
