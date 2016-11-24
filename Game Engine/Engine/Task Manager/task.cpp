//
//  task.cpp
//  Game Engine
//
//  Created by Indi Kernick on 15/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "task.hpp"

TaskManager *Task::getManager() {
  return taskManager;
}

void Task::kill() {
  done = true;
}

void Task::pause() {
  if (!paused) {
    paused = true;
    onPause();
  } else {
    throw std::logic_error("Tried to pause an already paused task");
  }
}

void Task::resume() {
  if (paused) {
    paused = false;
    onResume();
  } else {
    throw std::logic_error("Tried to resume an already running task");
  }
}
