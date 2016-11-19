//
//  cache.cpp
//  game engine
//
//  Created by Indi Kernick on 6/11/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "cache.hpp"

Resource::Cache::Cache(size_t size)
  : SIZE(size) {
  addLoader(std::make_shared<DefaultLoader>());
}

Resource::HandlePtr Resource::Cache::load(const std::string &path) {
  if (handleMap.find(path) == handleMap.end()) {
    LoaderPtr loader = findLoader(getExt(path));
    
    std::ifstream file(path);
    if (!file.is_open()) {
      throw std::runtime_error("Failed to open file");
    }
    
    file.seekg(0, std::ios::end);
    size_t rawSize = file.tellg();
    file.seekg(0, std::ios::beg);
    Memory::Buffer raw(loader->useRaw() ? alloc(rawSize)
                                        : Memory::Buffer::alloc(rawSize),
                       rawSize);
    file.read(reinterpret_cast<char *>(raw.begin()), rawSize);
    
    HandlePtr handle;
    if (loader->useRaw()) {
      handle = std::make_shared<Handle>(this, path, raw);
    } else {
      size_t size = loader->getSize(raw);
      Memory::Buffer resource(alloc(size), size);
      loader->process(raw, resource);
      handle = std::make_shared<Handle>(this, path, resource);
    }
    
    handleList.push_front(handle);
    handleMap[path] = handle;
    
    return handle;
  } else {
    return nullptr;
  }
}

void Resource::Cache::unLoad(const std::string &path) {
  free(path);
}

Resource::HandlePtr Resource::Cache::get(const std::string &path) {
  HandlePtr handle = find(path);
  if (handle == nullptr) {
    handle = load(path);
  } else {
    update(handle);
  }
  return handle;
}

void Resource::Cache::addLoader(LoaderPtr loader) {
  loaders.push_front(loader);
}

void Resource::Cache::freeLast() {
  if (!handleList.empty()) {
    handleMap.erase((*(--handleList.end()))->path);
    handleList.pop_back();
  }
}

void Resource::Cache::free(const std::string &path) {
  for (auto i = handleList.begin(); i != handleList.end(); i++) {
    if ((*i)->path == path) {
      allocSize -= (*i)->buffer.size();
      handleList.erase(i);
      break;
    }
  }
  handleMap.erase(path);
}

Resource::HandlePtr Resource::Cache::find(const std::string &path) {
  auto iter = handleMap.find(path);
  if (iter == handleMap.end()) {
    return nullptr;
  } else {
    return iter->second;
  }
}

void Resource::Cache::update(HandlePtr handle) {
  for (auto i = handleList.begin(); i != handleList.end(); i++) {
    if ((*i)->path == handle->path) {
      handleList.erase(i);
      handleList.push_front(handle);
      break;
    }
  }
}

Byte *Resource::Cache::alloc(size_t size) {
  if (size > SIZE) {
    //couldn't possibly fit
    throw Memory::OutOfMemory("tried to allocate resource larger than cache");
  }
  while (size > SIZE - allocSize) {
    if (handleList.empty()) {
      //all the handles are still in use
      throw Memory::OutOfMemory("Cannot allocate memory, cache is full");
    }
    freeLast();
  }
  allocSize += size;
  return Memory::Buffer::alloc(size);
}

void Resource::Cache::freed(size_t size) {
  allocSize -= size;
}

Resource::LoaderPtr Resource::Cache::findLoader(const std::string &ext) {
  for (auto i = loaders.begin(); i != loaders.end(); i++) {
    if ((*i)->canLoad(ext)) {
      return *i;
    }
  }
  throw std::runtime_error("Failed to find loader");
}

std::string Resource::Cache::getExt(const std::string &path) {
  auto lastDot = path.end();
  for (auto i = path.begin(); i != path.end(); i++) {
    if (*i == '.') {
      lastDot = i;
    }
  }
  if (lastDot == path.end()) {
    throw std::runtime_error("File doesn't have extension");
  }
  return {lastDot + 1, path.end()};
}
