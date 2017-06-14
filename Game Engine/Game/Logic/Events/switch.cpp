//
//  switch.cpp
//  Game Engine
//
//  Created by Indi Kernick on 14/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "switch.hpp"

Game::Events::SwitchOn::SwitchOn(const TilePos pos)
  : pos(pos) {}

Game::Events::SwitchOff::SwitchOff(const TilePos pos)
  : pos(pos) {}
