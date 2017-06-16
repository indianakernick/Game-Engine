//
//  logic impl.cpp
//  Game Engine
//
//  Created by Indi Kernick on 24/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "logic impl.hpp"

Game::LogicImpl::LogicImpl()
  : freqLimiter(DEFAULT_TICK_LENGTH),
    grid(Utils::CAPACITY, MAX_GRID_SIZE) {}

void Game::LogicImpl::init() {
  Logic::init();
  
  createTileID = evtMan->addListener(Utils::memFunWrap(this, &LogicImpl::onCreateTile));
  destroyTileID = evtMan->addListener(Utils::memFunWrap(this, &LogicImpl::onDestroyTile));
  resizeGridID = evtMan->addListener(Utils::memFunWrap(this, &LogicImpl::onResizeGrid));
  changeTickLengthID = evtMan->addListener(Utils::memFunWrap(this, &LogicImpl::onChangeTickLength));
}

void Game::LogicImpl::update(const uint64_t delta) {
  PROFILE(Game::LogicImpl::update);

  Logic::update(delta);
  
  if (state != State::RUNNING) {
    return;
  }
  
  freqLimiter.advance(delta);
  uint64_t count = std::min(MAX_TICKS_PER_UPDATE, freqLimiter.canDoMultiple());
  
  while (count--) {
    const auto end = grid.end();
    for (auto a = grid.begin(); a != end; ++a) {
      Actor::Ptr actor = *a;
      if (actor) {
        const TileComponent::Ptr tile(actor->getComponent<TileComponent>());
        tile->updateInputStates(getNeighbors(a.getPos()));
      }
    }
    for (auto a = grid.begin(); a != end; ++a) {
      Actor::Ptr actor = *a;
      if (actor) {
        const TileComponent::Ptr tile(actor->getComponent<TileComponent>());
        tile->preUpdate();
        actor->update(delta);
      }
    }
  }
}

void Game::LogicImpl::quit() {
  Logic::quit();
  
  evtMan->remListener(changeTickLengthID);
  evtMan->remListener(resizeGridID);
  evtMan->remListener(destroyTileID);
  evtMan->remListener(createTileID);
}

void Game::LogicImpl::onCreateTile(const Events::CreateTile::Ptr createTile) {
  if (state != State::EDITING) {
    return;
  }
  const size_t index = grid.index(createTile->pos);
  if (grid.access(index)) {
    evtMan->emit<Events::TileDestroyed>(createTile->pos);
  }
  grid.access(index) = factory.createActor(createTile->type, posToID(createTile->pos));
}

void Game::LogicImpl::onDestroyTile(const Events::DestroyTile::Ptr destroyTile) {
  if (state != State::EDITING) {
    return;
  }
  grid.access(destroyTile->pos) = nullptr;
}

void Game::LogicImpl::onResizeGrid(const Events::ResizeGrid::Ptr resizeGrid) {
  if (state != State::EDITING) {
    return;
  }
  
  const TilePos newSize = [this, resizeGrid] {
    if (resizeGrid->size.x > MAX_GRID_SIZE.x || resizeGrid->size.y > MAX_GRID_SIZE.y) {
      return MAX_GRID_SIZE;
    } else {
      return resizeGrid->size;
    }
  }();
  
  const TilePos size = grid.size();
  
  if (newSize.x < size.x) {
    const auto end = grid.end({newSize.x, 0}, size);
    for (auto a = grid.begin({newSize.x, 0}, size); a != end; ++a) {
      clearTile(a.getPos(), a.getIndex());
    }
  }
  
  if (newSize.y < size.y) {
    const TilePosScalar endX = std::min(size.x, newSize.x);
    const auto end = grid.end({0, newSize.y}, {endX, size.y});
    for (auto a = grid.begin({0, newSize.y}, {endX, size.y}); a != end; ++a) {
      clearTile(a.getPos(), a.getIndex());
    }
  }
  
  grid.resize(newSize);
}

void Game::LogicImpl::onChangeTickLength(const Events::ChangeTickLength::Ptr changeTickLength) {
  if (state == State::EDITING) {
    freqLimiter.setDuration(changeTickLength->duration);
  }
}

void Game::LogicImpl::onStartRunning(const Events::StartRunning::Ptr) {
  if (state == State::EDITING) {
    state = State::RUNNING;
  }
}

void Game::LogicImpl::onStopRunning(const Events::StopRunning::Ptr) {
  if (state == State::RUNNING) {
    state = State::EDITING;
  }
}

void Game::LogicImpl::clearTile(const TilePos pos, const size_t index) {
  if (grid.access(index)) {
    evtMan->emit<Events::TileDestroyed>(pos);
    grid.access(index) = nullptr;
  }
}

Game::TileComponent::Neighbors Game::LogicImpl::getNeighbors(const TilePos pos) const {
  Game::TileComponent::Neighbors neighbors;
  for (Math::DirType d = 0; d != 4; d++) {
    const Actor::Ptr actor = grid.access(pos + Math::toVec<TilePosScalar>(d));
    if (actor) {
      const TileComponent::Ptr tile(actor->getComponent<TileComponent>());
      neighbors[d] = tile.get();
    } else {
      neighbors[d] = nullptr;
    }
  }
  return neighbors;
}
