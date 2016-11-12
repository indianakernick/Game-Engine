//
//  material3d.hpp
//  game engine
//
//  Created by Indi Kernick on 18/09/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef material3d_hpp
#define material3d_hpp

#include "color.hpp"

namespace D3 {
  class Material {
  public:
    Material() = default;
    
    Graphics::Color color;
  };
}

#endif