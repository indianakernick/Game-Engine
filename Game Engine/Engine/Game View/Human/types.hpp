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
  using Coord = float;
  using CoordPx = int;
  using Color = glm::vec4;
  using FontSize = unsigned;
  using Point = glm::tvec2<Coord>;
  using PointPx = glm::tvec2<CoordPx>;
  using Polygon = std::vector<Point>;
  using Bounds = Math::RectPS<Coord>;
  using BoundsPx = Math::RectPS<CoordPx>;
  using TexCoords = Math::RectPP<Coord>;
  using TexCoordsPx = Math::RectPP<CoordPx>;
  
  const FontSize SMALLEST_FONT_SIZE = std::numeric_limits<FontSize>::min();
  const FontSize LARGEST_FONT_SIZE = std::numeric_limits<FontSize>::max();
}

#endif
