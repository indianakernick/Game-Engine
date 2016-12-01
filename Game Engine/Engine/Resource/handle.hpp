//
//  handle.hpp
//  Game Engine
//
//  Created by Indi Kernick on 6/11/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_handle_hpp
#define engine_resource_handle_hpp

#include "../Memory/buffer.hpp"
#include "id.hpp"
#include <memory>
#include "desc.hpp"

namespace Resource {
  class Cache;
  
  class Handle {
  friend class Cache;
  public:
    using Ptr = std::shared_ptr<Handle>;
  
    Handle(Cache *cache, ID id, Memory::Buffer buffer, Desc::Ptr desc);
    virtual ~Handle();
    
    const ID &getID() const;
    const Memory::Buffer &getBuffer() const;
    template <typename T>
    const std::shared_ptr<T> getDesc() const {
      return std::dynamic_pointer_cast<T>(desc);
    }
  protected:
    Cache * const cache;
    const ID id;
    const Memory::Buffer buffer;
    const Desc::Ptr desc;
  };
}

#include "cache.hpp"

#endif
