//
//  rect types.hpp
//  Game Engine
//
//  Created by Indi Kernick on 29/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_game_view_human_types_hpp
#define engine_game_view_human_types_hpp

#include <vector>
#include <glm/vec4.hpp>
#include "../../Math/rect.hpp"

namespace UI {
  using Height = int;
  using Color = glm::vec4;
  using Polygon = std::vector<glm::vec2>;
  using Bounds = Math::RectPS<float>;
  using TexCoords = Math::RectPP<float>;
}

#endif
