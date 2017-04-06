//
//  shader.hpp
//  Game Engine
//
//  Created by Indi Kernick on 6/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_loaders_shader_hpp
#define engine_resource_loaders_shader_hpp

#include "../loader.hpp"
#include "../Handles/shader.hpp"
#include "../../Platform/Interface/graphics library.hpp"

namespace Res {
  class ShaderLoader final : public Loader {
  public:
    const std::string &getName() const override;
    bool canLoad(std::experimental::string_view) const override;
    Handle::Ptr load(const ID &) const override;
  
  private:
    static Platform::Shader::Type getType(std::experimental::string_view);
  };
}

#endif
