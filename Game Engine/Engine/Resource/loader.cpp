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

FILE *Resource::Loader::openFile(const ID &id) {
  return fopen(absPath(id).c_str(), "r");
}

std::pair<Memory::Buffer, bool> Resource::Loader::readFile(const ID &id) {
  FILE *file = fopen(absPath(id).c_str(), "r");
  if (file) {
    fseek(file, 0, SEEK_END);
    Memory::Buffer buffer(ftell(file));
    rewind(file);
    fread(buffer.begin(), buffer.size(), 1, file);
    fclose(file);
    return {buffer, true};
  } else {
    return {Memory::Buffer(1), false};
  }
}
