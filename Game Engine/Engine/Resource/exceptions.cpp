//
//  exceptions.cpp
//  Game Engine
//
//  Created by Indi Kernick on 19/5/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "exceptions.hpp"

Res::InvalidResource::InvalidResource(const std::string &type, const std::string &error)
  : std::runtime_error("Invalid " + type + " resource: " + error) {}
