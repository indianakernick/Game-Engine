//
//  gate component.cpp
//  Game Engine
//
//  Created by Indi Kernick on 11/6/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "gate component.hpp"

Game::Gate::Gate()
  : tableChangeID(evtMan->addListener(Utils::memFunWrap(this, &Gate::onTableChange))) {}

Game::Gate::~Gate() {
  evtMan->remListener(tableChangeID);
}

void Game::Gate::update(uint64_t) {
  setAllOutputs(table.lookUpOutputs(getAllInputs()));
}

void Game::Gate::onTableChange(const Events::GateTableChange::Ptr tableChange) {
  if (tableChange->pos == IDToPos(actor->getID())) {
    table = tableChange->table;
  }
}
