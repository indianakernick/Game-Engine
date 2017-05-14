//
//  process.cpp
//  Game Engine
//
//  Created by Indi Kernick on 14/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "process.hpp"

bool Process::pause() {
  if (state == State::RUNNING || state == State::INITIAL) {
    state = State::PAUSED;
    return true;
  } else {
    return false;
  }
}

bool Process::resume() {
  if (state == State::PAUSED) {
    state = State::RUNNING;
    return true;
  } else {
    return false;
  }
}

bool Process::kill() {
  if (state == State::RUNNING || state == State::PAUSED) {
    state = State::KILLED;
    return true;
  } else {
    return false;
  }
}

bool Process::isAlive() const {
  return state == State::RUNNING || state == State::PAUSED;
}

bool Process::isDead() const {
  return state == State::SUCCEEDED ||
         state == State::FAILED    ||
         state == State::KILLED    ||
         state == State::ABORTED;
}

bool Process::hasCompleted() const {
  return state == State::SUCCEEDED || state == State::FAILED;
}

bool Process::hasNotStarted() const {
  return state == State::INITIAL;
}

bool Process::hasSucceeded() const {
  return state == State::SUCCEEDED;
}

bool Process::hasFailed() const {
  return state == State::FAILED;
}

bool Process::wasKilled() const {
  return state == State::KILLED;
}

bool Process::wasAborted() const {
  return state == State::ABORTED;
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
  if (state == State::RUNNING) {
    state = State::SUCCEEDED;
  }
}

void Process::fail() {
  if (state == State::RUNNING) {
    state = State::FAILED;
  }
}

void Process::init() {
  state = State::RUNNING;
  onInit();
}

void Process::abort() {
  if (state != State::ABORTED) {
    state = State::ABORTED;
    onAbort();
    if (nextProcess) {
      nextProcess->abort();
    }
  }
}
