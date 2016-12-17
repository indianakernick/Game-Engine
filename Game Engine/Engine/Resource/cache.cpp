//
//  cache.cpp
//  Game Engine
//
//  Created by Indi Kernick on 6/11/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "cache.hpp"

Resource::Cache::Cache(size_t size)
  : SIZE(size) {
  addLoader(std::make_shared<Loaders::Default>());
}

void Resource::Cache::load(const ID &id) {
  loadFile(id);
}

Resource::Handle::Ptr Resource::Cache::get(const ID &id) {
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

Byte *Resource::Cache::alloc(size_t size) {
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
  return Memory::Buffer::alloc(size);
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
  std::string ext(lastDot + 1, path.end());
  for (size_t i = 0; i < ext.size(); i++) {
    ext[i] = tolower(ext[i]);
  }
  return ext;
}

Resource::Handle::Ptr Resource::Cache::loadFile(const ID &id) {
  const std::string &path = id.getPath();
  Loader::Ptr loader = findLoader(getExt(path));
  
  std::ifstream file(Resource::path() + path);
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
  file.close();
  
  Handle::Ptr handle;
  if (loader->useRaw()) {
    Desc::Ptr desc = std::make_shared<Desc>();
    handle = std::make_shared<Handle>(this, id, raw, desc);
  } else {
    size_t size = loader->getSize(raw);
    Memory::Buffer resource(alloc(size), size);
    Desc::Ptr desc = loader->process(raw, resource);
    handle = std::make_shared<Handle>(this, id, resource, desc);
  }
  
  handleList.push_front(handle);
  handleMap[id] = handle;
  
  return handle;
}
