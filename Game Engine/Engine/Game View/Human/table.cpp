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

UI::Table::BadPos::BadPos()
  : std::out_of_range("Position out of range") {}

UI::Table::BadSize::BadSize()
  : std::out_of_range("Size out of range") {}

UI::Table::Table(const std::string &id)
  : Element(id) {}

UI::Table::Table(const std::string &id, const PointPx size)
  : Element(id), cells(), multiDimArray(size) {
  if (size.x <= 0 || size.y <= 0) {
    throw BadSize();
  }
  
  cells.reserve(RESERVE_SIZE.x * RESERVE_SIZE.y);
  cells.resize(size.x * size.y);
  setCellPos(size);
}

UI::TableCell &UI::Table::getCell(const PointPx pos) {
  const PointPx size = multiDimArray.getSize();
  if (pos.x < 0 || pos.y < 0 || pos.x >= size.x || pos.y >= size.y) {
    throw BadPos();
  }
  return cells[multiDimArray.posToIndex(pos)];
}

const UI::TableCell &UI::Table::getCell(const PointPx pos) const {
  const PointPx size = multiDimArray.getSize();
  if (pos.x < 0 || pos.y < 0 || pos.x >= size.x || pos.y >= size.y) {
    throw BadPos();
  }
  return cells[multiDimArray.posToIndex(pos)];
}

void UI::Table::resize(const PointPx newSize) {
  const PointPx size = multiDimArray.getSize();
  if (newSize == size) {
    return;
  }
  
  if (newSize.x <= 0 || newSize.y <= 0) {
    throw BadSize();
  }
  
  multiDimArray.setSize(newSize);
  
  const size_t newLength = newSize.x * newSize.y;
  const size_t oldLength = size.x * size.y;
  
  if (newLength < oldLength) {
    while (cells.size() != newLength) {
      cells.pop_back();
    }
    for (auto c = cells.begin(); c != cells.end(); ++c) {
      c->remAllChildren();
    }
  } else {
    while (cells.size() != newLength) {
      cells.emplace_back();
    }
    for (auto c = cells.begin(); c != cells.begin() + oldLength; ++c) {
      c->remAllChildren();
    }
  }
  
  setCellPos(newSize);
}

UI::PointPx UI::Table::getSize() const {
  return multiDimArray.getSize();
}

void UI::Table::setCellPos(const PointPx size) {
  const Point cellSize = {1.0f / size.x, 1.0f / size.y};
  const Point floatSize = size;
  for (size_t c = 0; c != cells.size(); c++) {
    const PointPx cellPos = multiDimArray.indexToPos(c);
    cells[c].getBounds().pos({cellPos.x / floatSize.x, cellPos.y / floatSize.y});
    cells[c].getBounds().size(cellSize);
  }
}
