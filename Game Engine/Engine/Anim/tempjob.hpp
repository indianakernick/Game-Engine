//
//  tempjob.hpp
//  Game Engine
//
//  Created by Indi Kernick on 5/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef tempjob_hpp
#define tempjob_hpp

#include "task.hpp"
#include <functional>
#include <ID/rand.hpp>
#include <map>
#include <list>
#include "blockallocatorview.hpp"

class TempJob : public Task {
public:
  //plenty
  static const size_t MAX_JOBS = 64;

  TempJob();
  
  //if jobfunc returns true then it will be called the next frame
  
  using JobFunc = std::function<bool (DeltaType delta)>;
  
  ID::Type addJob(JobFunc, ID::Type prev = ID::MAX_VAL);
  void cancelJob(ID::Type);
private:
  
  void update(DeltaType) override;
  // bytes
  struct Job {
    Job(JobFunc, Job *);
    
    JobFunc func;
    //the id of the job that must finish before this one can start
    //the id could before for a job in waitingJobs or startedJobs
    Job *prev;
    std::list<ID::Type> next;
    bool started = true;
  };
  
  using JobContainer = std::map<ID::Type, Job *>;
  using Iterator = JobContainer::iterator;
  using IterContainerPair = std::pair<Iterator, JobContainer *>;
  
  IterContainerPair getIter(ID::Type);
  
  JobContainer startedJobs;
  JobContainer waitingJobs;
  ID::Rand idGen;
  
  Memory::BlockAllocatorView<Job> allocator;
};

#endif
