//
//  task.hpp
//  Game Engine
//
//  Created by Indi Kernick on 15/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef task_hpp
#define task_hpp

#include <stdint.h>
#include <stdexcept>
#include <memory>

using DeltaType = uint64_t;

class TaskManager;

class Task {
friend class TaskManager;
public:
  using Ptr = std::shared_ptr<Task>;

  Task() = default;
  virtual ~Task() = default;

  TaskManager *getManager();
  
  void kill();
  void pause();
  void resume();
protected:
  virtual void update(DeltaType) = 0;
  virtual void onInit() {}
  virtual void onKill() {}
  virtual void onPause() {}
  virtual void onResume() {}
private:
  TaskManager *taskManager = nullptr;
  bool done = false;
  bool paused = false;
  bool started = false;
  int order = 0;
};

#endif
