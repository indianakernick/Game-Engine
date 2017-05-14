//
//  process.hpp
//  Game Engine
//
//  Created by Indi Kernick on 14/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_anim_process_hpp
#define engine_anim_process_hpp

#include <cstdint>
#include <memory>
#include <cassert>

class Process {
friend class ProcessManager;
public:
  using Ptr = std::shared_ptr<Process>;
  using Delta = uint64_t;

  Process() = default;
  virtual ~Process() = default;
  
  bool pause();
  bool resume();
  bool kill();
  
  bool isAlive() const;
  bool isDead() const;
  bool hasCompleted() const;
  bool hasNotStarted() const;
  bool hasSucceeded() const;
  bool hasFailed() const;
  bool wasKilled() const;
  bool wasAborted() const;
  
  ///Returns the process you passed in so you can string calls together like
  ///this process.next(otherProcess).next(afterOther).next(lastOne)
  Process::Ptr next(Process::Ptr);
  void cancelNext();
  
protected:
  void succeed();
  void fail();
  
private:
  enum class State : uint8_t {
    INITIAL,
    PAUSED,
    RUNNING,
    SUCCEEDED,
    FAILED,
    KILLED,
    ABORTED
  };
  
  Process::Ptr nextProcess = nullptr;
  State state = State::INITIAL;

  void init();
  void abort();

  virtual void update(Delta) = 0;
  virtual void onInit() {}
  virtual void onPause() {}
  virtual void onResume() {}
  virtual void onKill() {}
  virtual void onSucceed() {}
  virtual void onFail() {}
  virtual void onAbort() {}
};

#endif
