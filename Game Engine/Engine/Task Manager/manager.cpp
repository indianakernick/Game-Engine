//
//  manager.cpp
//  Game Engine
//
//  Created by Indi Kernick on 24/07/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "manager.hpp"

TaskManager::~TaskManager() {
  for (auto i = tasks.begin(); i != tasks.end(); ++i) {
    (*i)->abort();
  }
  for (auto i = pausedTasks.begin(); i != pausedTasks.end(); ++i) {
    (*i)->abort();
  }
}

void TaskManager::update(Task::Delta delta) {
  size_t sizeBefore = pausedTasks.size();
  
  pausedTasks.remove_if([this] (Task::Ptr task) {
    switch (task->state) {
      case Task::PAUSED:
        return false;
      case Task::RUNNING:
        task->onResume();
        tasks.push_back(task);
        return true;
      case Task::KILLED:
        task->onKill();
        return true;
      default:
        tasks.push_back(task);
        return true;
    }
  });
  
  orderChanged |= pausedTasks.size() < sizeBefore;
  
  if (orderChanged) {
    tasks.sort([] (Task::Ptr a, Task::Ptr b) {
      return a->order < b->order;
    });
    orderChanged = false;
  }
  
  sizeBefore = tasks.size();
  
  tasks.remove_if([this, delta] (Task::Ptr task) {
    switch (task->state) {
      case Task::INITIAL:
        task->init();
        return false;
      case Task::PAUSED:
        task->onPause();
        pausedTasks.push_back(task);
        return true;
      case Task::RUNNING:
        task->update(delta);
        return false;
      case Task::DONE:
        task->onDone();
        return true;
      case Task::KILLED:
        task->onKill();
        return true;
      case Task::ABORTED:
        task->onAbort();
        return true;
    }
  });
  
  orderChanged |= tasks.size() < sizeBefore;
}

void TaskManager::addTask(Task::Order order, Task::Ptr task) {
  task->order = order;
  tasks.push_back(task);
  orderChanged = true;
}

void TaskManager::remTask(Task::Ptr task) {
  task->kill();
}
