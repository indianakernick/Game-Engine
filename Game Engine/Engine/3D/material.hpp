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

namespace Graphics3D {
  class Material {
  public:
    Material() = default;
    Material(const FColor &diffuse, const FColor &ambient);
    
    float getAlpha() const;
    
    FColor diffuse;
    FColor ambient;
    FColor specular;
    float shininess = 0.0;
  };
}

#endif
