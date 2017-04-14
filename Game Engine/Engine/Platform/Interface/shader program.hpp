//
//  shader program.hpp
//  Game Engine
//
//  Created by Indi Kernick on 8/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_platform_interface_shader_program_hpp
#define engine_platform_interface_shader_program_hpp

#include <memory>
#include <string>
#include <cassert>

namespace Platform {
  class ShaderProgramLoadError final : public std::runtime_error {
  public:
    ShaderProgramLoadError(const char *);
  };

  class ShaderProgram {
  public:
    using Ptr = std::shared_ptr<ShaderProgram>;
  
    ShaderProgram(const std::string &);
    //forcing the class to be abstract so that the compiler knows all
    //ShaderProgram pointers are pointing to a ShaderProgramImpl.
    //ShaderProgramImpl is the only derived class of ShaderProgram so the
    //compiler should be able to optimize away dynamic casts and virtual
    //function calls
    virtual ~ShaderProgram() = 0;
    
    const std::string &getName() const;
    
  private:
    std::string name;
  };
}

#endif
