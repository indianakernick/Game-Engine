//
//  taskmanager.hpp
//  Game Engine
//
//  Created by Indi Kernick on 24/07/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef taskmanager_hpp
#define taskmanager_hpp

#include <set>
#include <cassert>
#include "task.hpp"
#include "profiler.hpp"
#include "../Time/delta.hpp"

class TaskManager {
public:
  TaskManager();
  ~TaskManager() = default;
  
  void add(int order, Task::Ptr);
  void kill(Task::Ptr);
  void pause(Task::Ptr);
  void resume(Task::Ptr);
  
  void run();
  void quit();
  bool isRunning();
private:
  bool running = false;
  bool willQuit = false;
  using CompareTask = bool (const Task::Ptr, const Task::Ptr);
  std::set<Task::Ptr, CompareTask> tasks;
  Time::Delta delta;
  
  bool has(Task::Ptr);
  
  static bool compare(const Task::Ptr, const Task::Ptr);
};

#endif
