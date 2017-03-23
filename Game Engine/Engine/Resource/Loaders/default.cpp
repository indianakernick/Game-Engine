//
//  default.cpp
//  Game Engine
//
//  Created by Indi Kernick on 19/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "default.hpp"

const std::string &Res::DefaultLoader::getName() const {
  static const std::string NAME = "Default";
  return NAME;
}

bool Res::DefaultLoader::canLoad(std::experimental::string_view) const {
  return true;
}

Res::Handle::Ptr Res::DefaultLoader::load(const ID &id) const {
  return std::make_shared<Default>(readFile(id));
}
