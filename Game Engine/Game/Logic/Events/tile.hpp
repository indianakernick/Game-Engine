//
//  tile.hpp
//  Game Engine
//
//  Created by Indi Kernick on 14/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef game_logic_events_tile_hpp
#define game_logic_events_tile_hpp

#include "../tile.hpp"
#include "../../../Engine/Event/event.hpp"

namespace Game {
  constexpr char TILE_IO_CHANGE_NAME[] = "Tile IO Change";

  namespace Events {
    class TileIOChange final : public StaticEvent<TileIOChange, TILE_IO_CHANGE_NAME> {
    public:
      TileIOChange(TilePos, TileIOTypes);
      
      const TilePos pos;
      const TileIOTypes ioTypes;
    };
  }
}

#endif
