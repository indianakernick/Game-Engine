//
//  default.cpp
//  Game Engine
//
//  Created by Indi Kernick on 19/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "default.hpp"

bool Resource::Loaders::Default::canLoad(const std::string &) {
  return true;
}

size_t Resource::Loaders::Default::getSize(const Memory::Buffer file) {
  return file.size();
}

bool Resource::Loaders::Default::useRaw() {
  return true;
}

//this function will never be called because useRaw returns true
Resource::Desc::Ptr Resource::Loaders::Default::process(const Memory::Buffer, Memory::Buffer) {
  return nullptr;
}
