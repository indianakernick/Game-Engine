//
//  taskmanager.cpp
//  Game Engine
//
//  Created by Indi Kernick on 24/07/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "manager.hpp"

TaskManager::TaskManager()
  : tasks(compare), delta(Time::MILLI) {}

void TaskManager::add(int order, Task::Ptr task) {
  assert(task);
  assert(!has(task));
  task->order = order;
  task->taskManager = this;
  tasks.insert(task);
}

void TaskManager::kill(Task::Ptr task) {
  assert(has(task));
  task->kill();
}

void TaskManager::pause(Task::Ptr task) {
  assert(has(task));
  task->pause();
}

void TaskManager::resume(Task::Ptr task) {
  assert(has(task));
  task->resume();
}

void TaskManager::run() {
  if (running)
    return;
  running = true;
  
  while (!willQuit && !tasks.empty()) {
    Profiler p("frame");
    double frameDuration = delta.get();
    for (auto i = tasks.begin(); i != tasks.end(); ++i) {
      if (!(*i)->started) {
        (*i)->onInit();
        (*i)->started = true;
      } else if (!(*i)->paused) {
        (*i)->update(frameDuration);
      }
    }
    
    for (auto i = tasks.begin(); i != tasks.end(); ++i) {
      if ((*i)->done) {
        (*i)->onKill();
        (*i)->taskManager = nullptr;
        tasks.erase(i);
        --i;
      }
    }
  }
  for (auto i = tasks.begin(); i != tasks.end(); ++i) {
    (*i)->onKill();
    (*i)->taskManager = nullptr;
  }
  tasks.clear();
  
  willQuit = false;
  running = false;
}

void TaskManager::quit() {
  willQuit = true;
}

bool TaskManager::isRunning() {
  return running;
}

bool TaskManager::has(Task::Ptr task) {
  for (auto i = tasks.begin(); i != tasks.end(); ++i) {
    if (*i == task) {
      return true;
    }
  }
  return false;
}

bool TaskManager::compare(const Task::Ptr a, const Task::Ptr b) {
  return a->order < b->order;
}
