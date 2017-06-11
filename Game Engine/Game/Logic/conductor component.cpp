//
//  conductor component.cpp
//  Game Engine
//
//  Created by Indi Kernick on 11/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "conductor component.hpp"

void Game::Conductor::update(uint64_t) {
  setAllOutputs(anyInputOn());
}
