//
//  material3d.hpp
//  Game Engine
//
//  Created by Indi Kernick on 18/09/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_material3d_hpp
#define engine_3d_material3d_hpp

#include "../Resource/id.hpp"
#include <glm/vec4.hpp>

namespace Graphics3D {
  class Material {
  public:
    Material() = default;
    Material(const glm::vec4 &diffuse, const glm::vec4 &ambient);
    
    float getAlpha() const;
    
    glm::vec4 diffuse;
    glm::vec4 ambient = {0.1f, 0.1f, 0.1f, 1.0f};
    glm::vec4 specular = {1.0f, 1.0f, 1.0f, 1.0f};
    float shininess = 0.0f;
    Resource::ID diffuseTexture;
  };
}

#endif
