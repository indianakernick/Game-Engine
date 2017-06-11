//
//  gate component.cpp
//  Game Engine
//
//  Created by Indi Kernick on 11/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "gate component.hpp"

Game::GateTable::GateTable()
  //4 zeros and 60 ones
  : table("0000111111111111111111111111111111111111111111111111111111111111") {}

Game::GateTable::Row Game::GateTable::lookUpOutputs(const Row inputStates) const {
  return (table.to_ullong() >> ((15 - inputStates.to_ullong()) * 4)) & 16;
}

void Game::GateTable::setRow(const size_t row, const Row data) {
  assert(row < 16);
  table &= data.to_ullong() << ((15 - row) * 4);
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
  GateTable::Row inputStates;
  for (uint8_t s = 0; s != 4; s++) {
    inputStates.set(s, getInputOr(s, false));
  }
  const GateTable::Row outputStates = table.lookUpOutputs(inputStates);
  for (uint8_t s = 0; s != 4; s++) {
    setOutputIfCan(s, outputStates.test(s));
  }
}

void Game::Gate::onTableChange(const Events::GateTableChange::Ptr tableChange) {
  if (tableChange->gateID == actor->getID()) {
    table = tableChange->table;
  }
}
