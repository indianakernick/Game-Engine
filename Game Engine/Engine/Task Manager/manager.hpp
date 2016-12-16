//
//  manager.hpp
//  Game Engine
//
//  Created by Indi Kernick on 24/07/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_task_manager_manager_hpp
#define engine_task_manager_manager_hpp

#include <list>
#include <cassert>
#include "task.hpp"
#include "profiler.hpp"
#include "../Time/delta.hpp"
#include <algorithm>

class TaskManager {
public:
  TaskManager() = default;
  ~TaskManager();
  
  void update(Task::Delta);
  
  void addTask(int order, Task::Ptr);
  void remTask(Task::Ptr);
  
private:
  std::list<Task::Ptr> tasks;
  std::list<Task::Ptr> pausedTasks;
  bool orderChanged = false;
};

#endif
