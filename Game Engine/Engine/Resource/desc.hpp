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
  ///A description of a resource. For an image it might be the size, for a
  ///sound file it might be the duration and sample rate
  class Desc {
  public:
    using Ptr = std::shared_ptr<Desc>;
  
    Desc() = default;
    virtual ~Desc() = default;
  };
}

#endif
