//
//  default.cpp
//  Game Engine
//
//  Created by Indi Kernick on 19/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "default.hpp"

const std::string &Resource::Loaders::Default::getName() {
  static const std::string NAME =  "Default";
  return NAME;
}

bool Resource::Loaders::Default::canLoad(const std::string &) {
  return true;
}

Resource::Handle::Ptr Resource::Loaders::Default::load(const ID &id) {
  std::pair<Memory::Buffer, bool> filePair = readFile(id);
  if (filePair.second) {
    return std::make_shared<Handles::Default>(filePair.first);
  } else {
    LOG_ERROR(RESOURCES, "Failed to open file \"%s\"", id.getPathC());
    return nullptr;
  }
}
