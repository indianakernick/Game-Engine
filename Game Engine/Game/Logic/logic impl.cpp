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
    actors(MAX_GRID_SIZE.x * MAX_GRID_SIZE.y),
    multiDimArray(MAX_GRID_SIZE) {}

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
    foreachTile<&LogicImpl::updateInputStates>({0, 0}, gridSize);
    foreachTile<uint64_t, &LogicImpl::updateTile>({0, 0}, gridSize, delta);
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
  const size_t index = getIndexFromPos(createTile->pos);
  if (actors[index]) {
    evtMan->emit<Events::TileDestroyed>(createTile->pos);
  }
  actors[index] = factory.createActor(createTile->type, posToID(createTile->pos));
}

void Game::LogicImpl::onDestroyTile(const Events::DestroyTile::Ptr destroyTile) {
  if (state != State::EDITING) {
    return;
  }
  actors[getIndexFromPos(destroyTile->pos)] = nullptr;
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
  
  if (newSize.x < gridSize.x) {
    foreachTile<&LogicImpl::clearTile>({newSize.x, 0}, gridSize);
  }
  
  if (newSize.y < gridSize.y) {
    foreachTile<&LogicImpl::clearTile>({0, newSize.y}, {std::min(gridSize.x, newSize.x), gridSize.y});
  }
  
  gridSize = newSize;
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

template <void (Game::LogicImpl::* MEM_FUN)(Game::TilePos, size_t)>
void Game::LogicImpl::foreachTile(const TilePos beginPos, const TilePos endPos) {
  static_assert(MultiDimArray::ORDER == Utils::Order::COL_MAJOR);
  
  for (TilePosScalar y = beginPos.y; y != endPos.y; y++) {
    for (TilePosScalar x = beginPos.x; x != endPos.x; x++) {
      const TilePos pos(x, y);
      (this->*MEM_FUN)(pos, multiDimArray.posToIndex(pos));
    }
  }
}

template <typename Data, void (Game::LogicImpl::* MEM_FUN)(Game::TilePos, size_t, Data)>
void Game::LogicImpl::foreachTile(const TilePos beginPos, const TilePos endPos, const Data data) {
  static_assert(MultiDimArray::ORDER == Utils::Order::COL_MAJOR);
  
  for (TilePosScalar y = beginPos.y; y != endPos.y; y++) {
    for (TilePosScalar x = beginPos.x; x != endPos.x; x++) {
      const TilePos pos(x, y);
      (this->*MEM_FUN)(pos, multiDimArray.posToIndex(pos), data);
    }
  }
}

void Game::LogicImpl::clearTile(const TilePos pos, const size_t index) {
  if (actors[index]) {
    evtMan->emit<Events::TileDestroyed>(pos);
    actors[index] = nullptr;
  }
}

void Game::LogicImpl::updateInputStates(const TilePos pos, const size_t index) {
  if (actors[index]) {
    const TileComponent::Ptr tile(actors[index]->getComponent<TileComponent>());
    tile->updateInputStates(getNeighbors(pos));
  }
}

void Game::LogicImpl::updateTile(const TilePos, const size_t index, const uint64_t delta) {
  if (actors[index]) {
    const TileComponent::Ptr tile(actors[index]->getComponent<TileComponent>());
    tile->preUpdate();
    actors[index]->update(delta);
  }
}

Game::TilePos Game::LogicImpl::getPosFromIndex(const size_t index) const {
  if (index >= actors.size()) {
    throw std::range_error("index out of range");
  }
  return multiDimArray.indexToPos(index);
}

size_t Game::LogicImpl::getIndexFromPos(const TilePos pos) const {
  if (pos.x < 0 || pos.y < 0 || pos.x >= gridSize.x || pos.y >= gridSize.y) {
    throw std::range_error("pos out of range");
  } else {
    return multiDimArray.posToIndex(pos);
  }
}

Game::Actor::Ptr Game::LogicImpl::getTile(const TilePos pos) const {
  if (pos.x < 0 || pos.y < 0 || pos.x >= gridSize.x || pos.y >= gridSize.y) {
    return nullptr;
  } else {
    return actors[multiDimArray.posToIndex(pos)];
  }
}

Game::TileComponent::Neighbors Game::LogicImpl::getNeighbors(const TilePos pos) const {
  Game::TileComponent::Neighbors neighbors;
  for (Math::DirType d = 0; d != 4; d++) {
    const Actor::Ptr actor = getTile(pos + Math::toVec<TilePosScalar>(d));
    if (actor) {
      const TileComponent::Ptr tile(actor->getComponent<TileComponent>());
      neighbors[d] = tile.get();
    } else {
      neighbors[d] = nullptr;
    }
  }
  return neighbors;
}
