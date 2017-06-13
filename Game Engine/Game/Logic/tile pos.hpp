//
//  tile pos.hpp
//  Game Engine
//
//  Created by Indi Kernick on 12/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef game_logic_tile_pos_hpp
#define game_logic_tile_pos_hpp

#include <glm/vec2.hpp>
#include "../../Engine/Utils/combine.hpp"
#include "../../Engine/Utils/int least.hpp"
#include "../../Engine/Game Logic/actor.hpp"

namespace Game {
  //The actor ID is derived from the position of the tile
  using TilePosScalar = Utils::int_least_t<sizeof(Actor::ID) / 2>;
  using TilePos = glm::tvec2<TilePosScalar>;
  
  TilePos IDToPos(Actor::ID);
  Actor::ID posToID(TilePos);
}

#endif
