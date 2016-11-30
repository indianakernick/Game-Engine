//
//  image.hpp
//  Game Engine
//
//  Created by Indi Kernick on 28/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_loaders_image_hpp
#define engine_resource_loaders_image_hpp

#include "../loader.hpp"
#include "../Descriptions/image.hpp"

namespace Resource {
  namespace Loaders {
    class Image : public Loader {
    public:
      static const int BYTE_DEPTH;
    
      bool canLoad(const std::string &fileExt) override;
      size_t getSize(const Memory::Buffer file) override;
      bool useRaw() override;
      Desc::Ptr process(const Memory::Buffer file, Memory::Buffer resource) override;
    };
  }
}

#endif
