//
//  font loader.cpp
//  Game Engine
//
//  Created by Indi Kernick on 11/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "font loader.hpp"

using namespace Platform;

FontLoadError::FontLoadError(const char *what)
  : std::runtime_error(what) {}
