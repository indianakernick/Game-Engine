//
//  taskmanager.hpp
//  game engine
//
//  Created by Indi Kernick on 24/07/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef taskmanager_hpp
#define taskmanager_hpp

#include <set>
#include <assert.h>
#include "task.hpp"
#include <memory>
#include "profiler.hpp"
#include "../Math/siconstants.hpp"

class TaskManager {
public:
  TaskManager();
  ~TaskManager() = default;
  
  void add(int order, std::shared_ptr<Task>);
  void kill(std::shared_ptr<Task>);
  void pause(std::shared_ptr<Task>);
  void resume(std::shared_ptr<Task>);
  
  void run();
  void quit();
  bool isRunning();
private:
  bool running = false;
  bool willQuit = false;
  std::set<std::shared_ptr<Task>, bool(*)(const std::shared_ptr<Task> &,
                                          const std::shared_ptr<Task> &)> tasks;
  
  bool has(std::shared_ptr<Task>);
  
  static bool compare(const std::shared_ptr<Task> &,
                      const std::shared_ptr<Task> &);
};

#endif
