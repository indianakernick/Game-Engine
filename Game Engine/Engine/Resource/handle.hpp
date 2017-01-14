//
//  handle.hpp
//  Game Engine
//
//  Created by Indi Kernick on 6/11/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_handle_hpp
#define engine_resource_handle_hpp

#include "id.hpp"
#include <memory>
#include "../Utils/logger.hpp"

namespace Resource {
  class Handle {
  friend class Cache;
  public:
    using Ptr = std::shared_ptr<Handle>;
  
    Handle() = default;
    virtual ~Handle();
    
    ///The size may change at any time while loading (during the call of
    ///Loader::load) but once the resource has loaded its size may not change
    void setSize(size_t);
    ///The size may change at any time while loading (during the call of
    ///Loader::load) but once the resource has loaded its size may not change
    void addSize(size_t);
    size_t getSize() const;
  private:
    size_t size = 0;
    ID id;
    bool loaded = false;
    std::function<void(Handle *)> destroyed;
  };
}

#endif
