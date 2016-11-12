//
//  loader.hpp
//  game engine
//
//  Created by Indi Kernick on 6/11/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef loader_hpp
#define loader_hpp

#include <cstddef>
#include <cstdint>
#include <string>

namespace Resource {
  class Loader {
  public:
    static const size_t HEADER_SIZE = 16;
    
    Loader() = default;
    virtual ~Loader() = default;
    
    ///Can you load this file based on its extension and first 16bytes
    virtual bool canLoad(const std::string &fileExt, const uint8_t *header) = 0;
    ///Get the size of a resource after it has been loaded from the file
    virtual size_t getSize(const uint8_t *file, size_t fileSize) = 0;
    ///Can the file be loaded in place, that is, copied directly into the
    ///cache and optionally post processed
    virtual bool inPlace() {
      return false;
    };
    ///Is the resource the same size as the file so that getSize never needs
    ///to be called
    virtual bool sameSize() {
      return false;
    };
    ///Process the file and write data to the resource
    virtual void process(const uint8_t *file, size_t fileSize, uint8_t *resource, size_t resourceSize) = 0;
    ///If inPlace() returns true then this will be called on the resource in
    ///the cache to perform in-place processing
    virtual void process(uint8_t *, size_t) {};
  };
}

#endif