//
//  font.hpp
//  Game Engine
//
//  Created by Indi Kernick on 11/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_loaders_font_hpp
#define engine_resource_loaders_font_hpp

#include "../loader.hpp"
#include "../Handles/font.hpp"
#include "../../Platform/Interface/font loader.hpp"

namespace Res {
  class FontLoader final : public Loader {
  public:
    const std::string &getName() const override;
    bool canLoad(std::experimental::string_view) const override;
    Handle::Ptr load(const ID &) const override;
  };
}

#endif
