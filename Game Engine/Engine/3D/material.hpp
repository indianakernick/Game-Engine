//
//  material3d.hpp
//  Game Engine
//
//  Created by Indi Kernick on 18/09/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_material3d_hpp
#define engine_3d_material3d_hpp

#include <SFML/Graphics/Color.hpp>

namespace D3 {
  class Material {
  public:
    Material() = default;
    
    sf::Color color;
  };
}

#endif
