//
//  process.hpp
//  Game Engine
//
//  Created by Indi Kernick on 14/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef process_hpp
#define process_hpp

#include <cstdint>
#include <memory>
#include <cassert>

class ProcessManager;

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
  
  bool isAlive();
  bool isDead();
  bool wasAborted();
  
  ///Returns the process you passed in so you can string calls together like
  ///this process.next(otherProcess).next(afterOther).next(lastOne)
  Process::Ptr next(Process::Ptr);
  void prev(Process::Ptr);
  void cancelNext();
protected:
  void succeed();
  void fail();
private:
  enum State : uint8_t {
    INITIAL,
    PAUSED,
    RUNNING,
    SUCCEEDED,
    FAILED,
    KILLED,
    ABORTED
  };
  
  State state = INITIAL;
  Process::Ptr nextProcess = nullptr;

  void init();
  void abort();

  virtual void update(Delta) = 0;
  virtual void onInit() {};
  virtual void onPause() {};
  virtual void onResume() {};
  virtual void onKill() {};
  virtual void onSucceed() {};
  virtual void onFail() {};
  virtual void onAbort() {};
};

#endif
