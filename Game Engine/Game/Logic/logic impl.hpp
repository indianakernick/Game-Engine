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
#include "tile component.hpp"
#include "Events/logic.hpp"
#include "../../Engine/Game Logic/base.hpp"
#include "../../Engine/Time/freq limiter.hpp"
#include "../../Engine/Utils/multi dim array.hpp"

namespace Game {
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
    ~LogicImpl() = default;
    
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
