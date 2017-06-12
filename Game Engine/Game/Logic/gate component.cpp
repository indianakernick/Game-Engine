//
//  gate component.cpp
//  Game Engine
//
//  Created by Indi Kernick on 11/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "gate component.hpp"

Game::TileComponent::States Game::GateTable::lookUpOutputs(
  const TileComponent::States inputStates
) const {
  if (outputs.count() == 0) {
    return {};
  }
  size_t rowIndex = getRowIndex(inputStates);
  
  TileComponent::States outputStates;
  
  for (size_t s = 0; s != 4; s++) {
    if (outputs.test(s)) {
      outputStates.set(s, table.test(rowIndex++));
    }
  }
  
  return outputStates;
}

void Game::GateTable::setOutputForInput(
  const TileComponent::States inputStates,
  const TileComponent::States outputStates
) {
  size_t rowIndex = getRowIndex(inputStates);
  
  for (size_t s = 0; s != 4; s++) {
    if (outputs.test(s)) {
      table.set(rowIndex++, outputStates.test(s));
    }
  }
}

void Game::GateTable::setIOSides(const TileComponent::IOTypes ioTypes) {
  for (size_t s = 0; s != 4; s++) {
    if (ioTypes[s] == TileComponent::IOType::IN) {
      inputs.set(s);
      outputs.reset(s);
    } else if (ioTypes[s] == TileComponent::IOType::OUT) {
      inputs.reset(s);
      outputs.set(s);
    } else {
      inputs.reset(s);
      outputs.reset(s);
    }
  }
}

size_t Game::GateTable::getRowIndex(const TileComponent::States inputStates) const {
  size_t inputIndex = 0;
  size_t rowIndex = 0;
  for (size_t s = 0; s != 4; s++) {
    if (inputs.test(s)) {
      rowIndex |= inputStates.test(s) << inputIndex++;
    }
  }
  return rowIndex * (4 - inputIndex);
}

Game::Events::GateTableChange::GateTableChange(const Actor::ID id, const GateTable table)
  : gateID(id), table(table) {}

Game::Gate::Gate() {
  tableChangeID = evtMan->addListener(Utils::memFunWrap(this, &Gate::onTableChange));
}

Game::Gate::~Gate() {
  evtMan->remListener(tableChangeID);
}

void Game::Gate::update(uint64_t) {
  setAllOutputs(table.lookUpOutputs(getAllInputs()));
}

void Game::Gate::onTableChange(const Events::GateTableChange::Ptr tableChange) {
  if (tableChange->gateID == actor->getID()) {
    table = tableChange->table;
  }
}
