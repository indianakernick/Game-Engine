//
//  shader.hpp
//  Game Engine
//
//  Created by Indi Kernick on 6/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_resource_handles_shader_hpp
#define engine_resource_handles_shader_hpp

#include "../handle.hpp"
#include "../../Platform/Interface/shader.hpp"

namespace Res {
  class Shader final : public Handle {
  public:
    using Ptr = std::shared_ptr<Shader>;
    
    Shader(Platform::Shader::Ptr);
    
    Platform::Shader::Ptr getShader() const;
    
  private:
    Platform::Shader::Ptr shader;
  };
}

#endif
