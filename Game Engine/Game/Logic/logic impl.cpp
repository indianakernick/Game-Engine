//
//  logic impl.cpp
//  Game Engine
//
//  Created by Indi Kernick on 24/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "logic impl.hpp"

Game::Events::CreateTile::CreateTile(const TilePos pos, const std::string &type)
  : pos(pos), type(type) {}

Game::Events::DestroyTile::DestroyTile(const TilePos pos)
  : pos(pos) {}

Game::Events::TileDestroyed::TileDestroyed(const TilePos pos)
  : pos(pos) {}

Game::Events::ResizeGrid::ResizeGrid(const TilePos size)
  : size(size) {}

Game::Events::ChangeTickLength::ChangeTickLength(const uint64_t duration)
  : duration(duration) {}

Game::LogicImpl::LogicImpl()
  : actors(MAX_GRID_SIZE.x * MAX_GRID_SIZE.y),
    multiDimArray(MAX_GRID_SIZE),
    createTileID(evtMan->addListener(Utils::memFunWrap(this, &LogicImpl::onCreateTile))),
    destroyTileID(evtMan->addListener(Utils::memFunWrap(this, &LogicImpl::onDestroyTile))),
    resizeGridID(evtMan->addListener(Utils::memFunWrap(this, &LogicImpl::onResizeGrid))),
    changeTickLengthID(evtMan->addListener(Utils::memFunWrap(this, &LogicImpl::onChangeTickLength))) {
}

Game::LogicImpl::~LogicImpl() {
  evtMan->remListener(changeTickLengthID);
  evtMan->remListener(resizeGridID);
  evtMan->remListener(destroyTileID);
  evtMan->remListener(createTileID);
}

void Game::LogicImpl::init() {
  Logic::init();
  
}

void Game::LogicImpl::update(const uint64_t delta) {
  Logic::update(delta);
  
  freqLimiter.advance(delta);
  uint64_t count = freqLimiter.canDoMultiple();
  if (count >= MAX_TICKS_PER_UPDATE) {
    count = MAX_TICKS_PER_UPDATE;
  }
  
  while (count--) {
    for (size_t a = 0; a != actors.size(); a++) {
      if (actors[a]) {
        TileComponent::Ptr tile(actors[a]->getComponent<TileComponent>());
        tile->updateInputStates(getNeighbors(getPosFromIndex(a)));
      }
    }
    
    for (auto a = actors.begin(); a != actors.end(); ++a) {
      if (*a) {
        TileComponent::Ptr tile((*a)->getComponent<TileComponent>());
        tile->preUpdate();
        (*a)->update(delta);
      }
    }
  }
}

void Game::LogicImpl::quit() {
  Logic::quit();
  
}

void Game::LogicImpl::onCreateTile(const Events::CreateTile::Ptr createTile) {
  const size_t index = getIndexFromPos(createTile->pos);
  if (actors[index]) {
    evtMan->emit<Events::TileDestroyed>(createTile->pos);
  }
  actors[index] = factory.createActor(createTile->type, posToID(createTile->pos));
  //const TileComponent::Ptr tile(actors[index]->getComponent<TileComponent>());
  //tile->setPos(createTile->pos);
}

void Game::LogicImpl::onDestroyTile(const Events::DestroyTile::Ptr destroyTile) {
  actors[getIndexFromPos(destroyTile->pos)] = nullptr;
}

void Game::LogicImpl::onResizeGrid(const Events::ResizeGrid::Ptr resizeGrid) {
  const TilePos newSize = [this, resizeGrid] {
    if (resizeGrid->size.x > MAX_GRID_SIZE.x || resizeGrid->size.y > MAX_GRID_SIZE.y) {
      return MAX_GRID_SIZE;
    } else {
      return resizeGrid->size;
    }
  }();
  
  if (newSize.x < gridSize.x) {
    clearRect({newSize.x, 0}, gridSize);
  }
  
  if (newSize.y < gridSize.y) {
    clearRect({0, newSize.y}, {std::min(gridSize.x, newSize.x), gridSize.y});
  }
  
  gridSize = newSize;
}

void Game::LogicImpl::onChangeTickLength(const Events::ChangeTickLength::Ptr changeTickLength) {
  freqLimiter.setDuration(changeTickLength->duration);
}

void Game::LogicImpl::clearRect(const TilePos beginPos, const TilePos endPos) {
  //assumes that MultiDimArray is set to ROW_MAJOR mode
  for (TilePosScalar y = beginPos.y; y != endPos.y; y++) {
    for (TilePosScalar x = beginPos.x; x != endPos.x; x++) {
      const size_t index = multiDimArray.posToIndex({x, y});
      if (actors[index]) {
        evtMan->emit<Events::TileDestroyed>(TilePos(x, y));
        actors[index] = nullptr;
      }
    }
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
