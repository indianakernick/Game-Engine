//
//  texture.cpp
//  Game Engine
//
//  Created by Indi Kernick on 5/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "texture.hpp"

Res::Texture::Texture(Platform::Texture::Ptr texture)
  : texture(texture) {
  assert(texture);
}

Platform::Texture::Ptr Res::Texture::getTexture() const {
  return texture;
}
