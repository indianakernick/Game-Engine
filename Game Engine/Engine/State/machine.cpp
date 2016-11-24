//
//  machine.cpp
//  Game Engine
//
//  Created by Indi Kernick on 18/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "machine.hpp"

FSM::Machine::Machine(State* initial)
  : state(initial) {
  assert(initial);
}

FSM::Machine::~Machine() {
  if (state) {
    state->leave();
    delete state;
    state = nullptr;
  }
}

void FSM::Machine::update() {
  State* newState = state->update(this);
  if (newState) {
    state->leave();
    delete state;
    state = newState;
    state->enter();
  }
}
