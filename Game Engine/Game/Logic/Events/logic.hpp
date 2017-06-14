//
//  logic.hpp
//  Game Engine
//
//  Created by Indi Kernick on 14/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef game_logic_events_logic_hpp
#define game_logic_events_logic_hpp

#include <string>
#include "../tile.hpp"
#include "../../../Engine/Event/event.hpp"

namespace Game {
  namespace Events {
    constexpr char CREATE_TILE_NAME[] = "Create Tile";
    
    ///View is telling Logic that a tile should be created
    class CreateTile final : public StaticEvent<CreateTile, CREATE_TILE_NAME> {
    public:
      CreateTile(TilePos, const std::string &);
      
      const TilePos pos;
      const std::string type;
    };
    
    constexpr char DESTROY_TILE_NAME[] = "Destroy Tile";
    
    ///View is telling Logic that a tile should be destroyed
    class DestroyTile final : public StaticEvent<DestroyTile, CREATE_TILE_NAME> {
    public:
      explicit DestroyTile(TilePos);
      
      const TilePos pos;
    };
    
    constexpr char TILE_DESTROYED_NAME[] = "Tile Destroyed";
    
    ///Logic is telling View that a tile was destroyed; Possibly due to a grid resize
    class TileDestroyed final : public StaticEvent<TileDestroyed, TILE_DESTROYED_NAME> {
    public:
      explicit TileDestroyed(TilePos);
      
      const TilePos pos;
    };
    
    constexpr char RESIZE_GRID_NAME[] = "Resize Grid";
    
    ///View is telling Logic that the grid should be resized
    class ResizeGrid final : public StaticEvent<ResizeGrid, RESIZE_GRID_NAME> {
    public:
      explicit ResizeGrid(TilePos);
      
      const TilePos size;
    };
    
    constexpr char CHANGE_TICK_LENGTH_NAME[] = "Change Tick Length";
    
    ///View is telling Logic to change the duration of a game tick
    class ChangeTickLength final : public StaticEvent<ChangeTickLength, CHANGE_TICK_LENGTH_NAME> {
    public:
      explicit ChangeTickLength(uint64_t);
      
      const uint64_t duration;
    };
    
    constexpr char SHOW_IO_NAME[] = "Show IO";
    
    ///Logic is telling View to show the IO types of the tiles
    class ShowIO final : public StaticEvent<ShowIO, SHOW_IO_NAME> {
    public:
      ShowIO() = default;
    };
    
    constexpr char HIDE_IO_NAME[] = "Hide IO";
    
    ///Logic is telling View to hide the IO types of the tiles
    class HideIO final : public StaticEvent<HideIO, HIDE_IO_NAME> {
    public:
      HideIO() = default;
    };
    
    constexpr char START_RUNNING_NAME[] = "Start Running";
    
    ///View is telling Logic to start the simulation
    class StartRunning final : public StaticEvent<StartRunning, START_RUNNING_NAME> {
    public:
      StartRunning() = default;
    };
    
    constexpr char STOP_RUNNING_NAME[] = "Stop Running";
    
    ///View is telling Logic to stop the simulation
    class StopRunning final : public StaticEvent<StopRunning, STOP_RUNNING_NAME> {
    public:
      StopRunning() = default;
    };
  }
}

#endif
