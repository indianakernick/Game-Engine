//
//  handle.cpp
//  Game Engine
//
//  Created by Indi Kernick on 6/11/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "handle.hpp"

Resource::Handle::Handle(Cache *cache, ID id, Memory::Buffer buffer, Desc::Ptr desc)
  : cache(cache), id(id), buffer(buffer), desc(desc) {}

Resource::Handle::~Handle() {
  cache->free(buffer.size());
}

const Resource::ID &Resource::Handle::getID() const {
  return id;
}

const Memory::Buffer &Resource::Handle::getBuffer() const {
  return buffer;
}

const Resource::Desc &Resource::Handle::getDesc() const {
  return *desc;
}
