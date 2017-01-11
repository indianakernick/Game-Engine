//
//  handle.cpp
//  Game Engine
//
//  Created by Indi Kernick on 6/11/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "handle.hpp"

Resource::Handle::~Handle() {
  if (destroyed) {
    destroyed(this);
  } else {
    LOG_WARNING(RESOURCES,
      "Handle to \"%s\" didn't have a destruction handler",
      id.getPathC());
  }
}

void Resource::Handle::setSize(size_t newSize) {
  if (!loaded) {
    size = newSize;
  } else {
    LOG_WARNING(RESOURCES,
      "Tried to set size of handle to \"%s\" after it was loaded",
      id.getPathC());
  }
}

void Resource::Handle::addSize(size_t deltaSize) {
  if (!loaded) {
    size += deltaSize;
  } else {
    LOG_WARNING(RESOURCES,
      "Tried to add size of handle to \"%s\" after it was loaded",
      id.getPathC());
  }
}

size_t Resource::Handle::getSize() const {
  return size;
}
