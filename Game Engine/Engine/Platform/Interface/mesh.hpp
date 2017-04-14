//
//  mesh.hpp
//  Game Engine
//
//  Created by Indi Kernick on 11/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_platform_interface_mesh_hpp
#define engine_platform_interface_mesh_hpp

#include <memory>

namespace Platform {
  class Mesh {
  public:
    using Ptr = std::shared_ptr<Mesh>;
  
    Mesh() = default;
    virtual ~Mesh() = default;
    
    virtual bool isAnimated() const = 0;
    virtual size_t getByteSize() const = 0;
  };
}

#endif
