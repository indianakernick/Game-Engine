//
//  handle.cpp
//  game engine
//
//  Created by Indi Kernick on 6/11/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "handle.hpp"

Resource::Handle::Handle(Cache *cache, std::string path, Memory::Buffer buffer)
  : cache(cache), path(path), buffer(buffer) {}

Resource::Handle::~Handle() {
  cache->free(buffer.size());
}

const std::string &Resource::Handle::getPath() {
  return path;
}

const Memory::Buffer &Resource::Handle::getBuffer() {
  return buffer;
}
