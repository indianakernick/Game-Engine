//
//  tempjob.hpp
//  game engine
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
  
  typedef std::function<bool (double delta)> JobFunc;
  
  ID::Type addJob(JobFunc, ID::Type prev = ID::MAX_VAL);
  void cancelJob(ID::Type);
private:
  
  void update(double) override;
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
  
  typedef std::map<ID::Type, Job *> JobContainer;
  typedef JobContainer::iterator Iterator;
  typedef std::pair<Iterator, JobContainer *> IterContainerPair;
  
  IterContainerPair getIter(ID::Type);
  
  JobContainer startedJobs;
  JobContainer waitingJobs;
  ID::Rand idGen;
  
  Buffer::BlockAllocatorView<Job> allocator;
};

#endif