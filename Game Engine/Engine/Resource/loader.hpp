//
//  loader.hpp
//  Game Engine
//
//  Created by Indi Kernick on 6/11/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_loader_hpp
#define engine_resource_loader_hpp

#include <cstddef>
#include <cstdint>
#include <string>
#include "../Memory/buffer.hpp"
#include "desc.hpp"

namespace Resource {
  class Loader {
  public:
    using Ptr = std::shared_ptr<Loader>;
  
    Loader() = default;
    virtual ~Loader() = default;
    
    ///Can you load this file based on its extension?
    virtual bool canLoad(const std::string &fileExt) = 0;
    ///Get the size of a resource after it has been loaded from the file
    virtual size_t getSize(const Memory::Buffer file) = 0;
    ///Can the resource be copied directly from the file to the resource?
    virtual bool useRaw() = 0;
    ///Process the file and write data to the resource
    virtual Desc::Ptr process(const Memory::Buffer file, Memory::Buffer resource) = 0;
  };
}

#endif
