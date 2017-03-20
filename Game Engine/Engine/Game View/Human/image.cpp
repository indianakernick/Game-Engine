//
//  image.cpp
//  Game Engine
//
//  Created by Indi Kernick on 20/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "image.hpp"

void UI::Image::setTexture(const Res::ID &newTexture) {
  texture = newTexture;
}

const Res::ID &UI::Image::getTexture() const {
  return texture;
}
