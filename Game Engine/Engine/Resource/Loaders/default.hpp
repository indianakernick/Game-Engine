//
//  default.hpp
//  Game Engine
//
//  Created by Indi Kernick on 19/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef default_hpp
#define default_hpp

#include "loader.hpp"

namespace Resource {
  namespace Loaders {
    class Default : public Loader {
    public:
      bool canLoad(const std::string &fileExt) override;
      size_t getSize(const Memory::Buffer file) override;
      bool useRaw() override;
      void process(const Memory::Buffer file, Memory::Buffer resource) override;
    };
  }
}

#endif
