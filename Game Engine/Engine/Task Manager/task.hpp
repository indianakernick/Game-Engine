//
//  task.hpp
//  game engine
//
//  Created by Indi Kernick on 15/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef task_hpp
#define task_hpp

#include <stdint.h>
#include <stdexcept>

class TaskManager;

class Task {
friend class TaskManager;
public:
  Task() = default;
  virtual ~Task() = default;

  TaskManager *getManager();
  
  void kill();
  void pause();
  void resume();
protected:
  virtual void update(double) = 0;
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