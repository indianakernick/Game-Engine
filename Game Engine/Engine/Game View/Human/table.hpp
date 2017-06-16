//
//  table.hpp
//  Game Engine
//
//  Created by Indi Kernick on 14/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_game_view_human_table_hpp
#define engine_game_view_human_table_hpp

#include "element.hpp"
#include "../../Utils/multi dim container.hpp"

namespace UI {
  class TableCell final : public Element {
  friend class Table;
  public:
    using Ptr = std::shared_ptr<TableCell>;
  
    TableCell();
    ~TableCell() = default;
  };

  class Table final : public Element {
  public:
    using Ptr = std::shared_ptr<Ptr>;
  
    explicit Table(const std::string &);
    Table(const std::string &, PointPx);
    ~Table() = default;
    
    ///Get a TableCell at a position
    TableCell &getCell(PointPx);
    ///Get a TableCell at a position
    const TableCell &getCell(PointPx) const;
    
    ///Change the number of TableCells in the Table
    void resize(PointPx);
    ///Get the size of the Table
    PointPx getSize() const;
  
  private:
    static constexpr PointPx RESERVE_SIZE = {64, 64};
  
    using MultiDimContainer = Utils::MultiDimContainer<
      TableCell, 2, Utils::Order::COL_MAJOR, CoordPx, size_t
    >;
    MultiDimContainer cells;
    
    void setCellPos(PointPx);
  };
}

#endif
