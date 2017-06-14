//
//  tile.cpp
//  Game Engine
//
//  Created by Indi Kernick on 14/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "tile.hpp"

Game::Events::TileIOChange::TileIOChange(const TilePos pos, const TileIOTypes ioTypes)
  : pos(pos), ioTypes(ioTypes) {}
