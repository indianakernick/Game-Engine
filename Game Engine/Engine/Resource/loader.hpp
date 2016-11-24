//
//  loader.hpp
//  Game Engine
//
//  Created by Indi Kernick on 6/11/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef loader_hpp
#define loader_hpp

#include <cstddef>
#include <cstdint>
#include <string>
#include "../Memory/buffer.hpp"

namespace Resource {
  class Loader {
  public:
    Loader() = default;
    virtual ~Loader() = default;
    
    ///Can you load this file based on its extension
    virtual bool canLoad(const std::string &fileExt) = 0;
    ///Get the size of a resource after it has been loaded from the file
    virtual size_t getSize(const Memory::Buffer file) = 0;
    ///Can the resource be copied directly from the file to the resource
    virtual bool useRaw() = 0;
    ///Process the file and write data to the resource
    virtual void process(const Memory::Buffer file, Memory::Buffer resource) = 0;
  };
  
  using LoaderPtr = std::shared_ptr<Loader>;
}

#endif
