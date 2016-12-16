//
//  task.cpp
//  Game Engine
//
//  Created by Indi Kernick on 15/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "task.hpp"

void Task::kill() {
  if (state == RUNNING || state == PAUSED) {
    state = KILLED;
  }
}

void Task::pause() {
  if (state == RUNNING || state == INITIAL) {
    state = PAUSED;
  }
}

void Task::resume() {
  if (state == PAUSED) {
    state = RUNNING;
  }
}

bool Task::isAlive() {
  return state == RUNNING || state == PAUSED;
}

bool Task::isDead() {
  return state == DONE ||
         state == KILLED ||
         state == ABORTED;
}

void Task::done() {
  if (state == RUNNING) {
    state = DONE;
  }
}

void Task::init() {
  state = RUNNING;
  onInit();
}

void Task::abort() {
  if (state != ABORTED) {
    state = ABORTED;
    onAbort();
  }
}
