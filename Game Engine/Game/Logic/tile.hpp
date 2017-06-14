//
//  tile.hpp
//  Game Engine
//
//  Created by Indi Kernick on 12/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef game_logic_tile_hpp
#define game_logic_tile_hpp

#include <array>
#include <bitset>
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
  
  enum class TileIOType {
    NONE,
    IN,
    OUT
  };
  
  using TileIOTypes = std::array<TileIOType, 4>;
  
  using TileStates = std::bitset<4>;
}

#endif
