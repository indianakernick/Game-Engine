//
//  lamp.cpp
//  Game Engine
//
//  Created by Indi Kernick on 14/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "lamp.hpp"

Game::Events::LampOn::LampOn(const TilePos pos)
  : pos(pos) {}

Game::Events::LampOff::LampOff(const TilePos pos)
  : pos(pos) {}
