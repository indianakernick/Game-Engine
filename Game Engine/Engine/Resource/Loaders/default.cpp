//
//  default.cpp
//  Game Engine
//
//  Created by Indi Kernick on 19/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "default.hpp"

const std::string &Res::DefaultLoader::getName() {
  static const std::string NAME =  "Default";
  return NAME;
}

bool Res::DefaultLoader::canLoad(const std::string &) {
  return true;
}

Res::Handle::Ptr Res::DefaultLoader::load(const ID &id) {
  std::pair<Memory::Buffer, bool> filePair = readFile(id);
  if (filePair.second) {
    return std::make_shared<Default>(filePair.first);
  } else {
    LOG_ERROR(RESOURCES, "Failed to open file \"%s\"", id.getPathC());
    return nullptr;
  }
}
