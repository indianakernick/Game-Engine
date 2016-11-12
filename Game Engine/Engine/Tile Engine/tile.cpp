//
//  tile.cpp
//  game engine
//
//  Created by Indi Kernick on 12/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "tile.hpp"

Geometry::Point TileEngine::Tile::getPos() {
  return pos;
}

TileEngine::Tile* TileEngine::Tile::getNeighbor(Geometry::Side side) {
  return *neighbors[Geometry::toNum(side)];
}

TileEngine::Tile* TileEngine::Tile::getNeighbor(Geometry::SideType side) {
  Geometry::validate(side);
  return neighbors[side] == nullptr ? nullptr : *neighbors[side];
}

TileEngine::Grid* TileEngine::Tile::getGrid() {
  return grid;
}