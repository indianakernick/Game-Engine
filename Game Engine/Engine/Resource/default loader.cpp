//
//  default loader.cpp
//  Game Engine
//
//  Created by Indi Kernick on 19/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "default loader.hpp"

bool Resource::DefaultLoader::canLoad(const std::string &, const Byte *) {
  return true;
}

size_t Resource::DefaultLoader::getSize(const Memory::Buffer file) {
  return file.size();
}

bool Resource::DefaultLoader::useRaw() {
  return true;
}

void process(const Memory::Buffer, Memory::Buffer) {}
