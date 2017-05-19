//
//  exceptions.hpp
//  Game Engine
//
//  Created by Indi Kernick on 19/5/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_exceptions_hpp
#define engine_resource_exceptions_hpp

#include <stdexcept>

namespace Res {
  class InvalidResource : std::runtime_error {
  public:
    InvalidResource(const std::string &, const std::string &);
  };
}

#endif
