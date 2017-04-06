//
//  texture.cpp
//  Game Engine
//
//  Created by Indi Kernick on 5/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "texture.hpp"

Platform::TextureLoadError::TextureLoadError(const char *what)
  : std::runtime_error(what) {}
