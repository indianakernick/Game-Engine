//
//  cache.cpp
//  Game Engine
//
//  Created by Indi Kernick on 6/11/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "cache.hpp"

Resource::Cache::Cache()
  : Cache(128 * Math::Byte::MEGA) {}

Resource::Cache::Cache(size_t size)
  : SIZE(size) {
  addLoader(std::make_shared<Loaders::Default>());
}

void Resource::Cache::load(const ID &id) {
  if (!id) {
    throw std::runtime_error("Tried to load a null resource");
  }
  loadFile(id);
}

const Resource::Handle::Ptr Resource::Cache::getBase(const ID &id) {
  if (!id) {
    throw std::runtime_error("Tried to get a null resource");
  }
  Handle::Ptr handle = find(id);
  if (handle == nullptr) {
    handle = loadFile(id);
  } else {
    update(handle);
  }
  return handle;
}

void Resource::Cache::addLoader(Loader::Ptr loader) {
  loaders.push_front(loader);
}

Resource::Handle::Ptr Resource::Cache::find(const ID &id) {
  auto iter = handleMap.find(id);
  if (iter == handleMap.end()) {
    return nullptr;
  } else {
    return iter->second;
  }
}

void Resource::Cache::update(Handle::Ptr handle) {
  for (auto i = handleList.begin(); i != handleList.end(); i++) {
    if ((*i)->id == handle->id) {
      handleList.erase(i);
      handleList.push_front(handle);
      break;
    }
  }
}

void Resource::Cache::alloc(size_t size) {
  if (size > SIZE) {
    //couldn't possibly fit
    throw Memory::OutOfMemory("Tried to allocate resource larger than cache");
  }
  while (size > SIZE - allocSize) {
    if (handleList.empty()) {
      //all the handles are still in use
      throw Memory::OutOfMemory("Cannot allocate memory, cache is full");
    }
    handleMap.erase(handleList.back()->id);
    handleList.pop_back();
  }
  allocSize += size;
}

void Resource::Cache::free(size_t size) {
  allocSize -= size;
}

Resource::Loader::Ptr Resource::Cache::findLoader(const std::string &ext) {
  for (auto i = loaders.begin(); i != loaders.end(); i++) {
    if ((*i)->canLoad(ext)) {
      return *i;
    }
  }
  throw std::runtime_error("Failed to find loader");
}

Resource::Handle::Ptr Resource::Cache::loadFile(const ID &id) {
  Loader::Ptr loader = findLoader(id.getExt());
  LOG_DEBUG(RESOURCES, "Loading \"%s\" with %s loader",
                       id.getPathC(), loader->getName().c_str());
  Handle::Ptr handle = loader->load(id);
  
  if (handle == nullptr) {
    LOG_ERROR(RESOURCES,
      "Failed to load \"%s\" with %s loader",
      id.getPathC(), loader->getName().c_str());
  } else {
    alloc(handle->size);
    handle->id = id;
    handle->loaded = true;
    handle->destroyed = [this](Handle *handle) {
      free(handle->size);
    };
    
    handleList.push_front(handle);
    handleMap[id] = handle;
  }
  
  return handle;
}

template <>
const Resource::Handle::Ptr Resource::Cache::get<Resource::Handle>(const ID &id) {
  return getBase(id);
}
