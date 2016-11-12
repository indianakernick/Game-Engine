//
//  grid.cpp
//  game engine
//
//  Created by Indi Kernick on 12/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "grid.hpp"

TileEngine::Grid::Grid(Geometry::Size size)
  : size(size) {
  assert(size.area());
  tiles = new Tile*[size.area()];
  memset(tiles,0,size.area() * 8);
}

TileEngine::Grid::~Grid() {
  dealloc();
}

Geometry::Size TileEngine::Grid::getSize() {
  return size;
}

void TileEngine::Grid::resize(Geometry::Size newSize) {
  if (newSize != size) {
    size = newSize;
    dealloc();
    tiles = new Tile*[size.area()];
  }
}

TileEngine::Tile* TileEngine::Grid::getTile(Geometry::Point point) {
  if (point.within(size)) {
    return tiles[point.toIndex(size)];
  } else {
    return nullptr;
  }
}

void TileEngine::Grid::setTile(Geometry::Point point, Tile* tile) {
  if (point.within(size)) {
    if (tile->grid == nullptr) {
      uint64_t i = point.toIndex(size);
      if (tiles[i] != nullptr) {
        delete tiles[i];
      }
      tiles[i] = tile;
      
      tile->pos = point;
      tile->neighbors[0] = getNeighborPtr(tile, 0);//up
      tile->neighbors[1] = getNeighborPtr(tile, 1);//right
      tile->neighbors[2] = getNeighborPtr(tile, 2);//down
      tile->neighbors[3] = getNeighborPtr(tile, 3);//left
    } else {
      throw std::logic_error("Cannot add a Tile which already belongs to a Grid");
    }
  } else {
    throw std::out_of_range("Point not within Grid");
  }
}

void TileEngine::Grid::remTile(Geometry::Point point) {
  if (point.within(size)) {
    int i = point.toIndex(size);
    if (tiles[i] != nullptr) {
      delete tiles[i];
      tiles[i] = nullptr;
    }
  }
}

void TileEngine::Grid::move(Geometry::Rect, Geometry::Rect) {
  
}

void TileEngine::Grid::clear(Geometry::Rect area) {
  if (area.intercept(size)) {
    Geometry::Point p;
    for (p.y = area.p.y; p.y < area.s.h; ++p.y) {
      if (p.y >= size.h) {
        break;
      }
      for (p.x = area.p.x; p.x < area.s.w; ++p.x) {
        if (p.x >= size.w) {
          break;
        }
        remTile(p);
      }
    }
  }
}

void TileEngine::Grid::foreach(std::function<void (Tile*&)> func, bool skipNull) {
  if (tiles != nullptr) {
    /*
    I always put the * next to the type instead of the variable because
    i thought that that * was apart of the type but ive just found out 
    that its not. i have to put ** next to end
    */
    for (Tile** i = tiles, **end = tiles + size.area(); i < end; ++i) {
      if (skipNull && *i != nullptr) {
        func(*i);
      }
    }
  }
}

void TileEngine::Grid::dealloc() {
  if (tiles != nullptr) {
    foreach([] (Tile*& tile) {
      //no need to check if tile is null because foreach does that
      delete tile;
      tile = nullptr;
    });
    delete[] tiles;
    tiles = nullptr;
  }
}

TileEngine::Tile **TileEngine::Grid::getNeighborPtr(Tile* tile, Geometry::DirType dir) {
  Geometry::validate(dir);
  Geometry::Point neighPoint = tile->pos.add(dir);
  if (neighPoint.within(size)) {
    return tiles + tile->pos.add(dir).toIndex(size);
  } else {
    return nullptr;
  }
}