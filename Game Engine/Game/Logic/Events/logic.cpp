//
//  logic.cpp
//  Game Engine
//
//  Created by Indi Kernick on 14/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "logic.hpp"

Game::Events::CreateTile::CreateTile(const TilePos pos, const std::string &type)
  : pos(pos), type(type) {}

Game::Events::DestroyTile::DestroyTile(const TilePos pos)
  : pos(pos) {}

Game::Events::TileDestroyed::TileDestroyed(const TilePos pos)
  : pos(pos) {}

Game::Events::ResizeGrid::ResizeGrid(const TilePos size)
  : size(size) {}

Game::Events::ChangeTickLength::ChangeTickLength(const uint64_t duration)
  : duration(duration) {}
