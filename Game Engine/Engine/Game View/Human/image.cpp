//
//  image.cpp
//  Game Engine
//
//  Created by Indi Kernick on 20/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "image.hpp"

UI::Image::Image(const std::string &id)
  : Element(std::make_unique<DefaultNodeImpl<Element>>(id)) {}
