//
//  animtask.hpp
//  Game Engine
//
//  Created by Indi Kernick on 6/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_anim_animtask_hpp
#define engine_anim_animtask_hpp

#include "task.hpp"
#include <memory>
#include <cassert>
#include <set>
#include <list>
#include "profiler.hpp"
#include "../Utils/debug.hpp"

class Animation : public Task {
public:
  enum class Dir : char {
    FORWARD,
    BACKWARD
  };
  
  class Job;
  using JobPtr = std::shared_ptr<Job>;
  
  class Job {
  friend class Animation;
  public:
    Job(DeltaType duration);
    Job(DeltaType duration,
        double progress,
        bool paused = true,
        Dir dir = Dir::FORWARD);
    Job(DeltaType duration, JobPtr prev);
    Job(DeltaType duration,
        JobPtr prev,
        double progress,
        bool paused,
        Dir dir);
    virtual ~Job() = default;
    
  protected:
    virtual void first();
    virtual void update(double progress, DeltaType offset) = 0;
    virtual void last();
  
    void setDuration(DeltaType);
    void setDir(Dir);
    void setProgress(double);
    void setOffset(DeltaType);
    void setPrev(JobPtr);
    
    DeltaType getDuration() const;
    Dir getDir() const;
    double getProgress() const;
    DeltaType getOffset() const;
    JobPtr getPrev() const;
    
    void pause();
    void resume();
    bool running() const;
  private:
    enum class Called : char {
      FIRST,
      LAST,
      UPDATE,
      NONE
    };
    void update(DeltaType delta, int frame);
    void step(DeltaType delta, int frame);
    void stepForward(DeltaType delta, int frame);
    void stepBackward(DeltaType delta, int frame);
  
    DeltaType duration;
    DeltaType offset = 0;
    Dir dir = Dir::FORWARD;
    bool paused = false;
    Called called = Called::NONE;
    int calledFrame = -1;
    
    //paused = false and first() will be called on the same frame prev->last() is called
    JobPtr prev = nullptr;
    //jobs whose prev points to this so that if this job is destroyed before it
    //is finished we can easily destroy jobs that may never start
    std::list<Job *> next;
  };
  
  Animation() = default;
  ~Animation();
  
  void addJob(JobPtr);
  void remJob(JobPtr);
private:
  std::set<JobPtr> jobs;
  int frame = 0;
  
  void update(DeltaType) override;
};

#endif
