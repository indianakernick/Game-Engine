//
//  shader.hpp
//  Game Engine
//
//  Created by Indi Kernick on 6/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_platform_interface_shader_hpp
#define engine_platform_interface_shader_hpp

#include <memory>
#include <stdexcept>

namespace Platform {
  class ShaderLoadError final : public std::runtime_error {
  public:
    ShaderLoadError(const char *);
  };
  
  class Shader {
  public:
    using Ptr = std::shared_ptr<Shader>;
    
    enum class Type : uint8_t {
      VERTEX,
      FRAGMENT,
      GEOMETRY
    };
    
    Shader(Type);
    virtual ~Shader() = default;
    
    Type getType() const;
    
  private:
    Type type;
  };
}

#endif
