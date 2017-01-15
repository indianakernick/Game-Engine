//
//  loader.cpp
//  Game Engine
//
//  Created by Indi Kernick on 10/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "loader.hpp"

std::string Resource::Loader::absPath(const ID &id) {
  return path() + id.getPath();
}

std::ifstream Resource::Loader::openFileStream(const ID &id) {
  return std::ifstream(absPath(id));
}

std::FILE *Resource::Loader::openFile(const ID &id) {
  return std::fopen(absPath(id).c_str(), "rb");
}

std::pair<Memory::Buffer, bool> Resource::Loader::readFile(const ID &id) {
  std::FILE *file = std::fopen(absPath(id).c_str(), "rb");
  if (file) {
    std::fseek(file, 0, SEEK_END);
    Memory::Buffer buffer(std::ftell(file));
    std::rewind(file);
    std::fread(buffer.begin(), buffer.size(), 1, file);
    std::fclose(file);
    return {buffer, true};
  } else {
    return {Memory::Buffer(1), false};
  }
}
