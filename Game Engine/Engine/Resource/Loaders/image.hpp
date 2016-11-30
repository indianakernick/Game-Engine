//
//  image.hpp
//  Game Engine
//
//  Created by Indi Kernick on 28/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef image_hpp
#define image_hpp

#include "../loader.hpp"

namespace Resource {
  namespace Loaders {
    class Image : public Loader {
    public:
      static const int DEPTH = 4;
    
      bool canLoad(const std::string &fileExt) override;
      size_t getSize(const Memory::Buffer file) override;
      bool useRaw() override;
      void process(const Memory::Buffer file, Memory::Buffer resource) override;
    };
  }
}

#endif
