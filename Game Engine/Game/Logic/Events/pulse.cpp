//
//  pulse.cpp
//  Game Engine
//
//  Created by Indi Kernick on 14/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "pulse.hpp"

Game::Events::PulseDurChange::PulseDurChange(
  const TilePos pos,
  const PulseDur on,
  const PulseDur off
) : pos(pos), onDuration(on), offDuration(off) {}
