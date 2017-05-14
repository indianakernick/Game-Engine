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

void ProcessManager::update(const Process::Delta delta) {
  switch (nextUpdate) {
    case NextUpdate::NORMAL:
      doUpdate(delta);
      break;
    case NextUpdate::PAUSE_ALL:
      doPauseAll();
      break;
    case NextUpdate::RESUME_ALL:
      doResumeAll();
      break;
    case NextUpdate::KILL_ALL:
      doKillAll();
      break;
  }
  nextUpdate = NextUpdate::NORMAL;
}

void ProcessManager::pauseAll() {
  nextUpdate = NextUpdate::PAUSE_ALL;
}

void ProcessManager::resumeAll() {
  nextUpdate = NextUpdate::RESUME_ALL;
}

void ProcessManager::killAll() {
  nextUpdate = NextUpdate::KILL_ALL;
}

void ProcessManager::addProcess(Process::Ptr process) {
  process->state = Process::State::INITIAL;
  processes.push_back(process);
}

void ProcessManager::remProcess(Process::Ptr process) {
  process->kill();
}

void ProcessManager::doUpdate(const Process::Delta delta) {
  pausedProcesses.remove_if([this](Process::Ptr process) {
    switch (process->state) {
      case Process::State::PAUSED:
        return false;
      case Process::State::RUNNING:
        process->onResume();
        processes.push_back(process);
        return true;
      case Process::State::KILLED:
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
      case Process::State::INITIAL:
        process->init();
        return false;
      case Process::State::PAUSED:
        process->onPause();
        pausedProcesses.push_back(process);
        return true;
      case Process::State::RUNNING:
        process->update(delta);
        return false;
      case Process::State::SUCCEEDED:
        process->onSucceed();
        if (process->nextProcess) {
          nextProcesses.push_back(process->nextProcess);
        }
        return true;
      case Process::State::FAILED:
        process->onFail();
        return true;
      case Process::State::KILLED:
        process->onKill();
        return true;
      case Process::State::ABORTED:
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
