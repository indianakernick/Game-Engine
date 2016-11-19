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
#include "path.hpp"

namespace Resource {
  class Cache {
  friend class Handle;
  public:
    Cache(size_t size);
    ~Cache() = default;
    
    void load(const std::string &path);
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
    
    //get a handle from its path by looking it up in handleMap
    HandlePtr find(const std::string &path);
    //moved handle to the front of the handleList
    void update(HandlePtr);
    //allocate memory in cache. may remove handles to free up space
    Byte *alloc(size_t size);
    //called by Handle destructor to tell the cache that the buffer was freed
    void free(size_t size);
    //find the loader that can loader a file with the given extension
    LoaderPtr findLoader(const std::string &ext);
    //get the extension given a path
    std::string getExt(const std::string &path);
    
    HandlePtr loadFile(const std::string &path);
  };
}

#endif
