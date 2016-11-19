//
//  handle.hpp
//  game engine
//
//  Created by Indi Kernick on 6/11/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef handle_hpp
#define handle_hpp

#include "../Memory/buffer.hpp"
#include <string>
#include <memory>

namespace Resource {
  class Cache;
  class Handle {
  friend class Cache;
  public:
    Handle(Cache *cache, std::string path, Memory::Buffer buffer);
    ~Handle();
    
    const Memory::Buffer buffer;
  private:
    Cache *cache = nullptr;
    std::string path;
  };
  
  using HandlePtr = std::shared_ptr<Handle>;
}

#include "cache.hpp"

#endif
