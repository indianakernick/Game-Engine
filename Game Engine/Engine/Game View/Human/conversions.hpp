//
//  conversions.hpp
//  Game Engine
//
//  Created by Indi Kernick on 30/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_game_view_human_conversions_hpp
#define engine_game_view_human_conversions_hpp

#include "types.hpp"

namespace UI {
  PointPx toPixels(Point, PointPx);
  BoundsPx toPixels(Bounds, PointPx);
  TexCoordsPx toPixels(TexCoords, PointPx);
  
  Point fromPixels(PointPx, PointPx);
  Bounds fromPixels(BoundsPx, PointPx);
  TexCoords fromPixels(TexCoordsPx, PointPx);
}

#endif
