//
//  texture.hpp
//  Game Engine
//
//  Created by Indi Kernick on 5/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_handles_texture_hpp
#define engine_resource_handles_texture_hpp

#include "../handle.hpp"
#include "../../Platform/Interface/texture.hpp"

namespace Res {
  class Texture final : public Handle {
  public:
    using Ptr = std::shared_ptr<Texture>;
    
    Texture(Platform::Texture::Ptr);
    
    Platform::Texture::Ptr getTexture() const;
  
  private:
    Platform::Texture::Ptr texture;
  };
}

#endif
