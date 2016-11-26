//
//  handle.cpp
//  Game Engine
//
//  Created by Indi Kernick on 6/11/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "handle.hpp"

Resource::Handle::Handle(Cache *cache, ID id, Memory::Buffer buffer)
  : cache(cache), id(id), buffer(buffer) {}

Resource::Handle::~Handle() {
  cache->free(buffer.size());
}

const Resource::ID &Resource::Handle::getID() {
  return id;
}

const Memory::Buffer &Resource::Handle::getBuffer() {
  return buffer;
}
