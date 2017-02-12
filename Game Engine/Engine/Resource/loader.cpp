//
//  loader.cpp
//  Game Engine
//
//  Created by Indi Kernick on 10/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "loader.hpp"

std::string Res::Loader::absPath(const ID &id) {
  return path() + id.getPath();
}

std::ifstream Res::Loader::openFileStream(const ID &id) {
  std::ifstream stream(absPath(id), std::ios::binary | std::ios::in);
  if (!stream.is_open()) {
    LOG_ERROR(RESOURCES, "Failed to open file stream \"%s\"", id.getPathC());
  }
  return stream;
}

std::FILE *Res::Loader::openFile(const ID &id) {
  std::FILE *file = std::fopen(absPath(id).c_str(), "rb");
  if (file == nullptr) {
    LOG_ERROR(RESOURCES, "Failed to open file \"%s\"", id.getPathC());
  }
  return file;
}

std::pair<Memory::Buffer, bool> Res::Loader::readFile(const ID &id) {
  std::FILE *file = openFile(id);
  if (file) {
    std::fseek(file, 0, SEEK_END);
    Memory::Buffer buffer(std::ftell(file));
    std::rewind(file);
    if (std::fread(buffer.begin(), buffer.size(), 1, file)) {
      std::fclose(file);
      return {buffer, true};
    } else {
      LOG_ERROR(RESOURCES, "Failed to read file \"%s\"", id.getPathC());
      std::fclose(file);
      return {Memory::Buffer(1), false};
    }
  } else {
    return {Memory::Buffer(1), false};
  }
}
