//
//  tempjob.hpp
//  Game Engine
//
//  Created by Indi Kernick on 5/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_anim_tempjob_hpp
#define engine_anim_tempjob_hpp

#include "task.hpp"
#include <functional>
#include "../ID/generator.hpp"
#include <map>
#include <list>
#include "blockallocatorview.hpp"

class TempJob : public Task {
public:
  //plenty
  static const size_t MAX_JOBS = 64;
  using ID = uint64_t;
  static const ID INVALID_JOB = std::numeric_limits<ID>::max();

  TempJob();
  
  //if jobfunc returns true then it will be called the next frame
  
  using JobFunc = std::function<bool (Task::Delta delta)>;
  
  ID addJob(JobFunc, ID prev = INVALID_JOB);
  void cancelJob(ID);
private:
  
  void update(Task::Delta) override;
  // bytes
  struct Job {
    Job(JobFunc, Job *);
    
    JobFunc func;
    //the id of the job that must finish before this one can start
    //the id could before for a job in waitingJobs or startedJobs
    Job *prev;
    std::list<ID> next;
    bool started = true;
  };
  
  using JobContainer = std::map<ID, Job *>;
  using Iterator = JobContainer::iterator;
  using IterContainerPair = std::pair<Iterator, JobContainer *>;
  
  IterContainerPair getIter(ID);
  
  JobContainer startedJobs;
  JobContainer waitingJobs;
  ::ID::Generator<ID> idGen;
  
  Memory::BlockAllocatorView<Job> allocator;
};

#endif
