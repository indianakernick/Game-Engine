//
//  desc.hpp
//  Game Engine
//
//  Created by Indi Kernick on 30/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_resrouce_desc_hpp
#define engine_resrouce_desc_hpp

#include <memory>

namespace Resource {
  ///A description of a resource that has been loaded. For an image it might be
  ///the size, for a sound file it might be the duration. If its unintuitive to
  ///store the resource in a block of memory then you could use this instead
  class Desc {
  public:
    using Ptr = std::shared_ptr<Desc>;
  
    Desc() = default;
    virtual ~Desc() = default;
  };
}

#endif
