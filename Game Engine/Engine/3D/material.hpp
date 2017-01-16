//
//  material3d.hpp
//  Game Engine
//
//  Created by Indi Kernick on 18/09/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_material3d_hpp
#define engine_3d_material3d_hpp

#include "color.hpp"
#include "../Resource/id.hpp"

namespace Graphics3D {
  class Material {
  public:
    Material() = default;
    Material(const Color4F &diffuse, const Color4F &ambient);
    
    float getAlpha() const;
    
    Color4F diffuse;
    Color4F ambient = {0.1f, 0.1f, 0.1f, 1.0f};
    Color4F specular = {1.0f, 1.0f, 1.0f, 1.0f};
    float shininess = 0.0f;
    Resource::ID diffuseTexture;
  };
}

#endif
