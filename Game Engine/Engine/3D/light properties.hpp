//
//  light properties.hpp
//  Game Engine
//
//  Created by Indi Kernick on 7/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_3d_light_properties_hpp
#define engine_3d_light_properties_hpp

#include <glm/vec3.hpp>

namespace Graphics3D {
  ///Information about a light that will be sent to the shader
  struct LightProperties {
    glm::vec3 color;
    float intensity = 10.0f;
    glm::vec3 pos;
  };
}

#endif
