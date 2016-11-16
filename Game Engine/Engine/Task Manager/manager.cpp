//
//  taskmanager.cpp
//  game engine
//
//  Created by Indi Kernick on 24/07/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "manager.hpp"

TaskManager::TaskManager()
  : tasks(compare) {}

void TaskManager::add(int order, std::shared_ptr<Task> task) {
  assert(task);
  assert(!has(task));
  task->order = order;
  task->taskManager = this;
  tasks.insert(task);
}

void TaskManager::kill(std::shared_ptr<Task> task) {
  assert(has(task));
  task->kill();
}

void TaskManager::pause(std::shared_ptr<Task> task) {
  assert(has(task));
  task->pause();
}

void TaskManager::resume(std::shared_ptr<Task> task) {
  assert(has(task));
  task->resume();
}

void TaskManager::run() {
  if (running)
    return;
  running = true;
  
  uint64_t lastFrameTime = Time::getNanoI();
  uint64_t frameDuration = 0;
  
  while (!willQuit && !tasks.empty()) {
    Profiler p("frame");
    for (auto i = tasks.begin(); i != tasks.end(); ++i) {
      if (!(*i)->started) {
        (*i)->onInit();
        (*i)->started = true;
      } else if (!(*i)->paused) {
        (*i)->update(frameDuration * Math::SI::NANO_MILLI);
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
    
    uint64_t currentTime = Time::getNanoI();
    frameDuration = currentTime - lastFrameTime;
    lastFrameTime = currentTime;
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

bool TaskManager::has(std::shared_ptr<Task> task) {
  for (auto i = tasks.begin(); i != tasks.end(); ++i) {
    if (*i == task) {
      return true;
    }
  }
  return false;
}

bool TaskManager::compare(const std::shared_ptr<Task> &a, const std::shared_ptr<Task> &b) {
  return a->order < b->order;
}
