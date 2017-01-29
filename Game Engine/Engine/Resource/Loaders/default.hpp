//
//  default.hpp
//  Game Engine
//
//  Created by Indi Kernick on 19/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_loaders_default_hpp
#define engine_resource_loaders_default_hpp

#include "loader.hpp"
#include "../Handles/default.hpp"

namespace Res {
  class DefaultLoader : public Loader {
  public:
    const std::string &getName() override;
    bool canLoad(const std::string &fileExt) override;
    Handle::Ptr load(const ID &) override;
  };
}

#endif
