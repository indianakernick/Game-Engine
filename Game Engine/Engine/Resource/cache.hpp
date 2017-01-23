//
//  cache.hpp
//  Game Engine
//
//  Created by Indi Kernick on 6/11/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_cache_hpp
#define engine_resource_cache_hpp

#include "loaders/default.hpp"
#include "../Memory/exceptions.hpp"
#include "path.hpp"
#include "id.hpp"
#include <list>
#include <unordered_map>
#include <fstream>
#include "../Math/byteconstants.hpp"
#include "../Time/stopwatch.hpp"

namespace Resource {
  class Cache {
  public:
    using Ptr = std::shared_ptr<Cache>;
  
    Cache();
    explicit Cache(size_t size);
    ~Cache() = default;
    
    void load(const ID &id);
    
    template <typename T = Handle>
    auto get(const ID &id) -> typename std::enable_if<std::is_base_of<Handle, T>::value, const std::shared_ptr<T>>::type {
      const Handle::Ptr basePtr = getBase(id);
      assert(basePtr);
      std::shared_ptr<T> ptr = std::dynamic_pointer_cast<T>(basePtr);
      assert(ptr);
      return ptr;
    }
    const Handle::Ptr getBase(const ID &id);
    
    void addLoader(Loader::Ptr);
  private:
    const size_t SIZE;
    size_t allocSize = 0;
    
    std::list<Loader::Ptr> loaders;
    //when a handle is requested, it is put in the front of this list so that
    //when the cache is full we can free the resources on the back of this list
    std::list<Handle::Ptr> handleList;
    std::unordered_map<ID, Handle::Ptr> handleMap;
    
    //get a handle from its path by looking it up in handleMap
    Handle::Ptr find(const ID &path);
    //moved handle to the front of the handleList
    void update(Handle::Ptr);
    //allocate memory in cache. may remove handles to free up space
    void alloc(size_t size);
    //called by Handle destructor to tell the cache that the memory was freed
    void free(size_t size);
    //find the loader that can load a file with the given extension
    Loader::Ptr findLoader(const std::string &ext);
    //load a file and put the handle in the list and map
    Handle::Ptr loadFile(const ID &path);
  };
  
  template <>
  const Handle::Ptr Cache::get<Handle>(const ID &id);
}

#endif
