//
//  grid.hpp
//  Game Engine
//
//  Created by Indi Kernick on 12/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_tile_engine_grid_hpp
#define engine_tile_engine_grid_hpp

#include <functional>
#include "../Geometry/rect.hpp"
#include <cassert>
#include "tile.hpp"
#include <stdexcept>

namespace TileEngine {
  class Grid {
  public:
    Grid(Geometry::Size);
    virtual ~Grid();
    
    Geometry::Size getSize();
    void resize(Geometry::Size);
    
    Tile* getTile(Geometry::Point);
    void setTile(Geometry::Point, Tile* tile);
    void remTile(Geometry::Point);
    
    void move(Geometry::Rect from, Geometry::Rect to);
    void clear(Geometry::Rect);
  protected:
    void foreach(std::function<void (Tile*&)> func, bool skipNull = true);
  private:
    Tile** tiles {nullptr};
    Geometry::Size size;
    
    void dealloc();
    Tile **getNeighborPtr(Tile*, Geometry::DirType);
  };
}

#endif
