//
//  default.hpp
//  Game Engine
//
//  Created by Indi Kernick on 10/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_handles_default_hpp
#define engine_resource_handles_default_hpp

#include "../handle.hpp"
#include "../../Memory/buffer.hpp"

namespace Resource {
  namespace Handles {
    class Default : public Handle {
    public:
      Default(const Memory::Buffer);
      
      const Memory::Buffer buf;
    };
  }
}

#endif
