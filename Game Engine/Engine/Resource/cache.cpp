//
//  cache.cpp
//  Game Engine
//
//  Created by Indi Kernick on 6/11/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "cache.hpp"

Res::Cache::Cache()
  : Cache(128 * Math::Byte::MEGA) {}

Res::Cache::Cache(size_t size)
  : SIZE(size) {
  addLoader(std::make_shared<DefaultLoader>());
}

void Res::Cache::load(const ID &id) {
  if (!id) {
    throw std::runtime_error("Tried to load a null resource");
  }
  loadFile(id);
}

const Res::Handle::Ptr Res::Cache::getBase(const ID &id) {
  if (!id) {
    throw std::runtime_error("Tried to get a null resource");
  }
  Handle::Ptr handle = find(id);
  if (handle == nullptr) {
    LOG_DEBUG(RESOURCES, "Cache miss");
    handle = loadFile(id);
  } else {
    update(handle);
  }
  return handle;
}

void Res::Cache::addLoader(Loader::Ptr loader) {
  loaders.push_front(loader);
}

Res::Handle::Ptr Res::Cache::find(const ID &id) {
  auto iter = handleMap.find(id);
  if (iter == handleMap.end()) {
    return nullptr;
  } else {
    return iter->second;
  }
}

void Res::Cache::update(Handle::Ptr handle) {
  for (auto i = handleList.begin(); i != handleList.end(); i++) {
    if ((*i)->id == handle->id) {
      handleList.erase(i);
      handleList.push_front(handle);
      break;
    }
  }
}

void Res::Cache::alloc(size_t size) {
  if (size == 0) {
    LOG_WARNING(RESOURCES, "Tried to allocate 0 bytes in the cache");
    return;
  }

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

void Res::Cache::free(size_t size) {
  if (size == 0) {
    LOG_WARNING(RESOURCES, "Tried to free 0 bytes from the cache");
    return;
  }
  allocSize -= size;
}

Res::Loader::Ptr Res::Cache::findLoader(const std::string &ext) {
  if (ext.empty()) {
    LOG_WARNING(RESOURCES, "Tried to find a loader for a file without an extension");
    //assuming the first loader is the default loader
    return loaders.front();
  } else {
    //this for loop will return the default loader for an empty extension
    for (auto i = loaders.begin(); i != loaders.end(); i++) {
      if ((*i)->canLoad(ext)) {
        return *i;
      }
    }
    throw std::runtime_error("Failed to find loader");
  }
}

Res::Handle::Ptr Res::Cache::loadFile(const ID &id) {
  Loader::Ptr loader = findLoader(id.getExt());
  LOG_DEBUG(RESOURCES,
    "Loading \"%s\" with %s loader",
    id.getPathC(), loader->getName().c_str());
  
  Handle::Ptr handle;
  float loadTime;
  try {
    Time::StopWatch<std::chrono::microseconds> stopWatch(true);
    handle = loader->load(id);
    loadTime = stopWatch.get() / 1000.0f;
  } catch (FileError &e) {
    LOG_ERROR(RESOURCES,
      "Failed load resource \"%s\": A file error occured: %s",
      id.getPathC(), e.what());
  }
  
  if (handle == nullptr) {
    LOG_ERROR(RESOURCES,
      "Failed to load \"%s\" with %s loader",
      id.getPathC(), loader->getName().c_str());
  } else {
    LOG_DEBUG(RESOURCES,
      "Loading took %.3lfms and the size is %.3lfkb",
      loadTime, handle->size / 1024.0f);
  
    addHandle(id, handle);
  }
  
  return handle;
}

void Res::Cache::addHandle(const ID &id, Handle::Ptr handle) {
  alloc(handle->size);
  handle->id = id;
  handle->loaded = true;
  handle->destroyed = [this](Handle *handle) {
    free(handle->size);
  };
  handleList.push_front(handle);
  handleMap[id] = handle;
}

template <>
const Res::Handle::Ptr Res::Cache::get<Res::Handle>(const ID &id) {
  return getBase(id);
}
