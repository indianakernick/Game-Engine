//
//  program 3d.hpp
//  Game Engine
//
//  Created by Indi Kernick on 7/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_program_3d_hpp
#define engine_3d_program_3d_hpp

#include <glm/mat4x4.hpp>
#include "material.hpp"
#include <vector>
#include <memory>
#include "light properties.hpp"

namespace Graphics3D {
  class Program3D {
  public:
    using Ptr = std::shared_ptr<Program3D>;
  
    Program3D() = default;
    virtual ~Program3D() = default;
    
    virtual void load() = 0;
    
    virtual void setModel(const glm::mat4 &) = 0;
    virtual void setView(const glm::mat4 &) = 0;
    virtual void setProj(const glm::mat4 &) = 0;
    virtual void setMat() = 0;
    
    virtual void setMaterial(const Material &) = 0;
    virtual void setLights(const std::vector<LightProperties> &lights) = 0;
  };
}

#endif
