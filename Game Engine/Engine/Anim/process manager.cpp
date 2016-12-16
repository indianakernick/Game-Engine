//
//  process manager.cpp
//  Game Engine
//
//  Created by Indi Kernick on 14/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "process manager.hpp"

//what is a for loop?

ProcessManager::~ProcessManager() {
  auto abort = [](Process::Ptr process) {
    process->abort();
  };
  std::for_each(processes.begin(), processes.end(), abort);
  std::for_each(pausedProcesses.begin(), pausedProcesses.end(), abort);
}

void ProcessManager::update(Process::Delta delta) {
  switch (nextUpdate) {
    case NORMAL:
      doUpdate(delta);
      break;
    case PAUSE_ALL:
      doPauseAll();
      break;
    case RESUME_ALL:
      doResumeAll();
      break;
    case KILL_ALL:
      doKillAll();
      break;
  }
  nextUpdate = NORMAL;
}

void ProcessManager::pauseAll() {
  nextUpdate = PAUSE_ALL;
}

void ProcessManager::resumeAll() {
  nextUpdate = RESUME_ALL;
}

void ProcessManager::killAll() {
  nextUpdate = KILL_ALL;
}

void ProcessManager::addProcess(Process::Ptr process) {
  processes.push_back(process);
}

void ProcessManager::remProcess(Process::Ptr process) {
  process->kill();
}

void ProcessManager::doUpdate(Process::Delta delta) {
  pausedProcesses.remove_if([this](Process::Ptr process) {
    switch (process->state) {
      case Process::PAUSED:
        return false;
      case Process::RUNNING:
        process->onResume();
        processes.push_back(process);
        return true;
      case Process::KILLED:
        process->onKill();
        return true;
      default:
        processes.push_back(process);
        return true;
    }
  });
  
  ProcessList nextProcesses;
  
  processes.remove_if([this, &nextProcesses, delta](Process::Ptr process) {
    switch (process->state) {
      case Process::INITIAL:
        process->init();
        return false;
      case Process::PAUSED:
        process->onPause();
        pausedProcesses.push_back(process);
        return true;
      case Process::RUNNING:
        process->update(delta);
        return false;
      case Process::SUCCEEDED:
        process->onSucceed();
        if (process->nextProcess) {
          nextProcesses.push_back(process->nextProcess);
        }
        return true;
      case Process::FAILED:
        process->onFailed();
        return true;
      case Process::KILLED:
        process->onKill();
        return true;
      case Process::ABORTED:
        //a process can only be put into an ABORTED state
        //when the ProcessManager dtor is called so this code won't run
        process->onAbort();
        return true;
    }
  });
  
  processes.splice(processes.end(), nextProcesses);
}

void ProcessManager::doPauseAll() {
  std::for_each(processes.begin(), processes.end(), [](Process::Ptr process) {
    if (process->pause()) {
      process->onPause();
    }
  });
  pausedProcesses.splice(pausedProcesses.end(), processes);
  processes.clear();
}

void ProcessManager::doResumeAll() {
  std::for_each(pausedProcesses.begin(), pausedProcesses.end(), [](Process::Ptr process) {
    if (process->resume()) {
      process->onResume();
    }
  });
  pausedProcesses.splice(processes.end(), pausedProcesses);
  pausedProcesses.clear();
}

void ProcessManager::doKillAll() {
  auto kill = [](Process::Ptr process) {
    if (process->kill()) {
      process->onKill();
    }
  };
  std::for_each(processes.begin(), processes.end(), kill);
  std::for_each(pausedProcesses.begin(), pausedProcesses.end(), kill);
  processes.clear();
  pausedProcesses.clear();
}
