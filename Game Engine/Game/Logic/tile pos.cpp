//
//  tile pos.cpp
//  Game Engine
//
//  Created by Indi Kernick on 12/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "tile pos.hpp"

Game::TilePos Game::IDToPos(const Actor::ID id) {
  return Utils::decomposeAndConstruct<TilePos, TilePosScalar, TilePosScalar>(id);
}

Game::Actor::ID Game::posToID(const TilePos pos) {
  return Utils::combine(pos.x, pos.y);
}
