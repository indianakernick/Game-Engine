//
//  task.hpp
//  Game Engine
//
//  Created by Indi Kernick on 15/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_task_manager_task_hpp
#define engine_task_manager_task_hpp

#include <cstdint>
#include <memory>

class Task {
friend class TaskManager;
public:
  using Ptr = std::shared_ptr<Task>;
  using Delta = uint64_t;
  using Order = int;

  Task() = default;
  virtual ~Task() = default;

  void kill();
  void pause();
  void resume();
  
  bool isAlive();
  bool isDead();
protected:
  void done();
private:
  enum State {
    INITIAL,
    PAUSED,
    RUNNING,
    DONE,
    KILLED,
    ABORTED
  };

  State state = INITIAL;
  Order order = 0;
  
  void init();
  void abort();
  
  virtual void update(Delta) = 0;
  virtual void onInit() {}
  virtual void onKill() {}
  virtual void onPause() {}
  virtual void onResume() {}
  virtual void onDone() {}
  virtual void onAbort() {}
};

#endif
