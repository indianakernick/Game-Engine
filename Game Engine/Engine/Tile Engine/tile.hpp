//
//  tile.hpp
//  game engine
//
//  Created by Indi Kernick on 12/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef tile_hpp
#define tile_hpp

#include <Geometry/point.hpp>
#include <Geometry/dir.hpp>

namespace TileEngine {
  class Grid;

  class Tile {
  friend class Grid;
  public:
    Tile() = default;
    virtual ~Tile() = default;
    
    Geometry::Point getPos();
  protected:
    Tile* getNeighbor(Geometry::Side);
    Tile* getNeighbor(Geometry::SideType);
    Grid* getGrid();
    
    virtual void update() {};
  private:
    Tile** neighbors[4] {nullptr, nullptr, nullptr, nullptr};
    Grid* grid {nullptr};
    Geometry::Point pos;
  };
}

#endif