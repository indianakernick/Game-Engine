//
//  image.cpp
//  Game Engine
//
//  Created by Indi Kernick on 20/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "image.hpp"

void UI::Image::setTexture(const std::string &newTexture) {
  texture = newTexture;
}

const std::string &UI::Image::getTexture() const {
  return texture;
}
