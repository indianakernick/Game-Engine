//
//  gate.cpp
//  Game Engine
//
//  Created by Indi Kernick on 14/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "gate.hpp"

Game::TileStates Game::GateTable::lookUpOutputs(
  const TileStates inputStates
) const {
  if (outputs.count() == 0) {
    return {};
  }
  size_t rowIndex = getRowIndex(inputStates);
  
  TileStates outputStates;
  
  for (size_t s = 0; s != 4; s++) {
    if (outputs.test(s)) {
      outputStates.set(s, table.test(rowIndex++));
    }
  }
  
  return outputStates;
}

void Game::GateTable::setOutputForInput(
  const TileStates inputStates,
  const TileStates outputStates
) {
  size_t rowIndex = getRowIndex(inputStates);
  
  for (size_t s = 0; s != 4; s++) {
    if (outputs.test(s)) {
      table.set(rowIndex++, outputStates.test(s));
    }
  }
}

void Game::GateTable::setIOSides(const TileIOTypes ioTypes) {
  for (size_t s = 0; s != 4; s++) {
    if (ioTypes[s] == TileIOType::IN) {
      inputs.set(s);
      outputs.reset(s);
    } else if (ioTypes[s] == TileIOType::OUT) {
      inputs.reset(s);
      outputs.set(s);
    } else {
      inputs.reset(s);
      outputs.reset(s);
    }
  }
}

size_t Game::GateTable::getRowIndex(const TileStates inputStates) const {
  size_t inputIndex = 0;
  size_t rowIndex = 0;
  for (size_t s = 0; s != 4; s++) {
    if (inputs.test(s)) {
      rowIndex |= inputStates.test(s) << inputIndex++;
    }
  }
  return rowIndex * (4 - inputIndex);
}

Game::Events::GateTableChange::GateTableChange(const TilePos pos, const GateTable table)
  : pos(pos), table(table) {}
