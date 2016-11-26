//
//  cache.hpp
//  Game Engine
//
//  Created by Indi Kernick on 6/11/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef cache_hpp
#define cache_hpp

#include "handle.hpp"
#include "loader.hpp"
#include "default loader.hpp"
#include "../Memory/exceptions.hpp"
#include "path.hpp"
#include "id.hpp"
#include <list>
#include <map>
#include <fstream>

namespace Resource {
  class Cache {
  friend class Handle;
  public:
    explicit Cache(size_t size);
    ~Cache() = default;
    
    void load(const ID &path);
    Handle::Ptr get(const ID &path);
    
    void addLoader(Loader::Ptr);
  private:
    const size_t SIZE;
    size_t allocSize = 0;
    
    std::list<Loader::Ptr> loaders;
    //when a handle is requested, it is put in the front of this list so that
    //when the cache is full we can free the resources on the back of this list
    std::list<Handle::Ptr> handleList;
    std::map<ID, Handle::Ptr> handleMap;
    
    //get a handle from its path by looking it up in handleMap
    Handle::Ptr find(const ID &path);
    //moved handle to the front of the handleList
    void update(Handle::Ptr);
    //allocate memory in cache. may remove handles to free up space
    Byte *alloc(size_t size);
    //called by Handle destructor to tell the cache that the buffer was freed
    void free(size_t size);
    //find the loader that can loader a file with the given extension
    Loader::Ptr findLoader(const std::string &ext);
    //get the extension given a path
    std::string getExt(const std::string &path);
    
    Handle::Ptr loadFile(const ID &path);
  };
}

#endif
