//
//  process.cpp
//  Game Engine
//
//  Created by Indi Kernick on 14/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "process.hpp"

bool Process::pause() {
  if (state != PAUSED) {
    state = PAUSED;
    return true;
  } else {
    return false;
  }
}

bool Process::resume() {
  if (state == PAUSED) {
    state = RUNNING;
    return true;
  } else {
    return false;
  }
}

bool Process::kill() {
  if (state == RUNNING || state == PAUSED) {
    state = KILLED;
    return true;
  } else {
    return false;
  }
}

bool Process::isAlive() {
  return state == RUNNING || state == PAUSED;
}

bool Process::isDead() {
  return state == SUCCEEDED ||
         state == FAILED ||
         state == KILLED ||
         state == ABORTED;
}

bool Process::wasAborted() {
  return state == ABORTED;
}

Process::Ptr Process::next(Process::Ptr newNextProcess) {
  assert(newNextProcess);
  nextProcess = newNextProcess;
  return newNextProcess;
}

void Process::cancelNext() {
  if (nextProcess) {
    nextProcess->abort();
    nextProcess = nullptr;
  }
}

void Process::succeed() {
  if (state == RUNNING) {
    state = SUCCEEDED;
  }
}

void Process::fail() {
  if (state == RUNNING) {
    state = FAILED;
  }
}

void Process::init() {
  state = RUNNING;
  onInit();
}

void Process::abort() {
  if (state != ABORTED) {
    state = ABORTED;
    onAbort();
    if (nextProcess) {
      nextProcess->abort();
    }
  }
}
