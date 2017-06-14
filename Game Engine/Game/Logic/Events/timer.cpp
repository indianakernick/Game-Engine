//
//  timer.cpp
//  Game Engine
//
//  Created by Indi Kernick on 14/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "timer.hpp"

Game::Events::TimerDurChange::TimerDurChange(const TilePos pos, const TimerDur duration)
  : pos(pos), duration(duration) {}
