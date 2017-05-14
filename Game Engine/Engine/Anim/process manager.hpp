//
//  process manager.hpp
//  Game Engine
//
//  Created by Indi Kernick on 14/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_anim_process_manager_hpp
#define engine_anim_process_manager_hpp

#include "process.hpp"
#include <list>
#include <algorithm>

class ProcessManager {
public:
  using Ptr = std::shared_ptr<ProcessManager>;

  ProcessManager() = default;
  ~ProcessManager();
  
  void update(Process::Delta);
  
  void pauseAll();
  void resumeAll();
  void killAll();
  
  void addProcess(Process::Ptr);
  void remProcess(Process::Ptr);
  
private:
  using ProcessList = std::list<Process::Ptr>;
  ProcessList processes;
  ProcessList pausedProcesses;
  
  enum class NextUpdate : uint8_t {
    NORMAL,
    PAUSE_ALL,
    RESUME_ALL,
    KILL_ALL
  };
  
  NextUpdate nextUpdate = NextUpdate::NORMAL;
  
  void doUpdate(Process::Delta);
  void doPauseAll();
  void doResumeAll();
  void doKillAll();
};

#endif
