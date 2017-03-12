//
//  program manager.hpp
//  Game Engine
//
//  Created by Indi Kernick on 12/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_program_manager_hpp
#define engine_3d_program_manager_hpp

#include <memory>
#include "program type.hpp"
#include <glm/mat4x4.hpp>
#include <glm/vec4.hpp>
#include <vector>
#include "Scene/light.hpp"
#include "material.hpp"
#include "../Resource/id.hpp"

namespace Graphics3D {
  class ProgramManager {
  public:
    using Ptr = std::shared_ptr<ProgramManager>;
    
    ProgramManager() = default;
    virtual ~ProgramManager() = default;
    
    virtual void loadAll() = 0;
    virtual void bind(ProgType) = 0;
    
    virtual void setModel(const glm::mat4 &model) = 0;
    virtual void setCamera(const glm::mat4 &view, const glm::mat4 &proj) = 0;
    virtual void setMaterial(const Material &mat) = 0;
    virtual void setLights(const std::vector<Scene::Light::AllProps> &lights,
                           const std::vector<glm::vec3> &lightsPos,
                           const std::vector<glm::vec3> &lightsDir) = 0;
    virtual void setBones(const std::vector<glm::mat4> &bones) = 0;
    
    virtual void setMaterial(const glm::vec4 &, const Res::ID &) = 0;
  };
}

#endif
