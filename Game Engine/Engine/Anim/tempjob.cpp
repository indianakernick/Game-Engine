//
//  tempjob.cpp
//  game engine
//
//  Created by Indi Kernick on 5/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "tempjob.hpp"

TempJob::TempJob()
  : allocator(MAX_JOBS) {}

ID::Type TempJob::addJob(JobFunc func, ID::Type prev) {
  Job *prevPtr = nullptr;
  if (prev != ID::MAX_VAL) {
    IterContainerPair pair = getIter(prev);
    assert(pair.second);
    prevPtr = pair.first->second;
  }
  
  Job *job = allocator.alloc(func, prevPtr);
  ID::Type id = idGen.create();
  if (prevPtr) {
    prevPtr->next.push_back(id);
  }
  
  if (prev == ID::MAX_VAL) {
    startedJobs[id] = job;
  } else {
    job->started = false;
    waitingJobs[id] = job;
  }
  return id;
}

void TempJob::cancelJob(ID::Type id) {
  IterContainerPair pair = getIter(id);
  if (pair.second != nullptr) {
    Job *job = pair.first->second;
    while (job->next.begin() != job->next.end()) {
      cancelJob(job->next.front());
    }
    for (auto i = job->prev->next.begin(); i != job->prev->next.end(); ++i) {
      if (*i == id) {
        job->prev->next.erase(i);
        break;
      }
    }
    allocator.free(job);
    pair.second->erase(pair.first);
  }
}

void TempJob::update(double delta) {
  for (auto i = waitingJobs.begin(); i != waitingJobs.end(); ++i) {
    Job *job = i->second;
    if (job->started) {
      //move this job into the startedJobs container
      startedJobs[i->first] = job;
      waitingJobs.erase(i);
    }
  }
  START_LOOP:
  for (auto i = startedJobs.begin(); i != startedJobs.end(); ++i) {
    Job *job = i->second;
    if (!job->func(delta)) {
      //find all waiting jobs waiting for this job to finish and start them
      for (auto j = job->next.begin(); j != job->next.end(); ++j) {
        auto iter = waitingJobs.find(*j);
        assert(iter != waitingJobs.end());
        iter->second->func(delta);
        iter->second->started = true;
      }
      if (i == startedJobs.begin()) {
        startedJobs.erase(i);
        goto START_LOOP;
      } else {
        startedJobs.erase(i);
        --i;
      }
      //make the id of this job avaible for use
      idGen.remove(i->first);
    }
  }
}

TempJob::IterContainerPair TempJob::getIter(ID::Type id) {
  Iterator iter = startedJobs.find(id);
  if (iter == startedJobs.end()) {
    Iterator iter = waitingJobs.find(id);
    if (iter == waitingJobs.end()) {
      return {iter,nullptr};
    } else {
      return {iter, &waitingJobs};
    }
  } else {
    return {iter, &startedJobs};
  }
}

TempJob::Job::Job(JobFunc func, Job *prev)
  : func(func), prev(prev) {}