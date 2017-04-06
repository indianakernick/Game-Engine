//
//  texture.hpp
//  Game Engine
//
//  Created by Indi Kernick on 5/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_loaders_texture_hpp
#define engine_resource_loaders_texture_hpp

#include "../loader.hpp"
#include "../Handles/texture.hpp"
#include "../../Platform/Interface/graphics library.hpp"
#include "../../../Libraries/stb_image.h"

namespace Res {
  class TextureLoader final : public Loader {
  public:
    const std::string &getName() const override;
    bool canLoad(std::experimental::string_view) const override;
    Handle::Ptr load(const ID &id) const override;
  };
}

#endif
