//
//  types.hpp
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
  using FontSize = unsigned;
  using Point = glm::tvec2<float>;
  using PointPx = glm::tvec2<int>;
  using Polygon = std::vector<Point>;
  using Bounds = Math::RectPS<float>;
  using BoundsPx = Math::RectPS<int>;
  using TexCoords = Math::RectPP<float>;
  using TexCoordsPx = Math::RectPP<int>;
  
  const FontSize SMALLEST_FONT_SIZE = std::numeric_limits<FontSize>::min();
  const FontSize LARGEST_FONT_SIZE = std::numeric_limits<FontSize>::max();
}

#endif
