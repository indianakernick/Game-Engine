//
//  logic impl.hpp
//  Game Engine
//
//  Created by Indi Kernick on 24/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef game_logic_impl_hpp
#define game_logic_impl_hpp

#include <vector>
#include "tile pos.hpp"
#include "tile component.hpp"
#include "../../Engine/Event/manager.hpp"
#include "../../Engine/Utils/multi dim array.hpp"
#include "../../Engine/Game Logic/base.hpp"
#include "../../Engine/Time/freq limiter.hpp"

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

  class LogicImpl final : public Logic {
  public:
    enum class State : uint8_t {
      EDITING,
      RUNNING
    };
    
    static constexpr TilePos MAX_GRID_SIZE = {1024, 1024};
    static constexpr uint64_t DEFAULT_TICK_LENGTH = 100;
    static constexpr uint64_t MAX_TICKS_PER_UPDATE = 8;
    
    LogicImpl();
    ~LogicImpl();
    
    void init() override;
    void update(uint64_t) override;
    void quit() override;
    
  private:
    Time::DeltaFreqLimiter<uint64_t> freqLimiter;
    std::vector<Actor::Ptr> actors;
    TilePos gridSize;
    using MultiDimArray = Utils::MultiDimArray<
      2, Utils::Order::COL_MAJOR, TilePosScalar, size_t
    >;
    MultiDimArray multiDimArray;
    State state = State::EDITING;
    
    EventManager::ListenerID createTileID,
                             destroyTileID,
                             resizeGridID,
                             changeTickLengthID;
    
    void onCreateTile(Events::CreateTile::Ptr);
    void onDestroyTile(Events::DestroyTile::Ptr);
    void onResizeGrid(Events::ResizeGrid::Ptr);
    void onChangeTickLength(Events::ChangeTickLength::Ptr);
    void onStartRunning(Events::StartRunning::Ptr);
    void onStopRunning(Events::StopRunning::Ptr);
    
    template <void (LogicImpl::* MEM_FUN)(TilePos, size_t)>
    void foreachTile(TilePos, TilePos);
    template <typename Data, void (LogicImpl::* MEM_FUN)(TilePos, size_t, Data)>
    void foreachTile(TilePos, TilePos, Data);
    
    void clearTile(TilePos, size_t);
    void updateInputStates(TilePos, size_t);
    void updateTile(TilePos, size_t, uint64_t);
    
    TilePos getPosFromIndex(size_t) const;
    size_t getIndexFromPos(TilePos) const;
    Actor::Ptr getTile(TilePos) const;
    TileComponent::Neighbors getNeighbors(TilePos) const;
  };
}

#endif
