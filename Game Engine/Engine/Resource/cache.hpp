//
//  cache.hpp
//  game engine
//
//  Created by Indi Kernick on 6/11/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef cache_hpp
#define cache_hpp

#include <cstddef>
#include "handle.hpp"
#include "loader.hpp"
#include "default loader.hpp"
#include <list>
#include <map>
#include <fstream>
#include "../Memory/exceptions.hpp"

namespace Resource {
  class Cache {
  public:
    Cache(size_t size);
    ~Cache() = default;
    
    HandlePtr load(const std::string &path);
    void unLoad(const std::string &path);
    HandlePtr get(const std::string &path);
    
    void addLoader(LoaderPtr);
  private:
    const size_t SIZE;
    size_t allocSize = 0;
    
    std::list<LoaderPtr> loaders;
    //when a handle is requested, it is put in the front of this list so that
    //when the cache is full we can free the resources on the back of this list
    std::list<HandlePtr> handleList;
    std::map<std::string, HandlePtr> handleMap;
    
    //free the last handle in the handleList
    void freeLast();
    //free a handle
    void free(const std::string &path);
    //get a handle from its path by looking it up in handleMap
    HandlePtr find(const std::string &path);
    //moved handle to the front of the handleList
    void update(HandlePtr);
    //allocate memory in cache. may remove handles to free up space
    Byte *alloc(size_t size);
    //called by Handle destructor to tell the cache that the buffer was freed
    void freed(size_t size);
    
    LoaderPtr findLoader(const std::string &ext);
    
    std::string getExt(const std::string &path);
  };
}

#endif
