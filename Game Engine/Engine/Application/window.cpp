//
//  window.cpp
//  Game Engine
//
//  Created by Indi Kernick on 16/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "window.hpp"

const std::string &Window::getTitle() const {
  return title;
}

Geometry::Size Window::getSize() const {
  return size;
}
