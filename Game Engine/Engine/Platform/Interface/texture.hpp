//
//  texture.hpp
//  Game Engine
//
//  Created by Indi Kernick on 5/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_platform_interface_texture_hpp
#define engine_platform_interface_texture_hpp

#include <memory>
#include <stdexcept>

namespace Platform {
  class TextureLoadError final : public std::runtime_error {
  public:
    TextureLoadError(const char *);
  };
  
  class Texture {
  public:
    using Ptr = std::shared_ptr<Texture>;
    
    Texture() = default;
    virtual ~Texture() = 0;
  };
};

#endif
