//
//  table.cpp
//  Game Engine
//
//  Created by Indi Kernick on 14/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "table.hpp"

//Table Cells are special. They aren't children of Table so they don't need
//unique IDs
UI::TableCell::TableCell()
  : Element("Cell") {
  getBounds().sizeAxis(Axis::BOTH);
}

UI::Table::Table(const std::string &id)
  : Element(id), cells(Utils::CAPACITY, RESERVE_SIZE) {}

UI::Table::Table(const std::string &id, const PointPx size)
  : Element(id), cells(RESERVE_SIZE, size) {
  setCellPos(size);
}

UI::TableCell &UI::Table::getCell(const PointPx pos) {
  return cells.access(pos);
}

const UI::TableCell &UI::Table::getCell(const PointPx pos) const {
  return cells.access(pos);
}

void UI::Table::resize(const PointPx newSize) {
  const PointPx capacity = cells.capacity();
  if (capacity.x < newSize.x || capacity.y < newSize.y) {
    cells.reserve({newSize.x * 2, newSize.y * 2});
    cells.resize(newSize);
  } else {
    const auto end = cells.end();
    for (auto c = cells.begin(); c != end; ++c) {
      c->remAllChildren();
    }
  }
  
  setCellPos(newSize);
}

UI::PointPx UI::Table::getSize() const {
  return cells.size();
}

void UI::Table::setCellPos(const PointPx size) {
  const Point cellSize = {1.0f / size.x, 1.0f / size.y};
  const Point floatSize = size;
  const auto end = cells.end();
  for (auto c = cells.begin(); c != end; ++c) {
    const PointPx cellPos = c.getPos();
    TableCell &cell = *c;
    cell.getBounds().pos({cellPos.x / floatSize.x, cellPos.y / floatSize.y});
    cell.getBounds().size(cellSize);
  }
}
