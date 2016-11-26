//
//  animtask.cpp
//  Game Engine
//
//  Created by Indi Kernick on 6/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "animtask.hpp"

Animation::Job::Job(DeltaType duration)
  : Job(duration, nullptr, 0, true, Dir::FORWARD) {}

Animation::Job::Job(DeltaType duration, double progress, bool paused, Dir dir)
  : Job(duration, nullptr, progress, paused, dir) {}

Animation::Job::Job(DeltaType duration, JobPtr prev)
  : Job(duration, prev, 0, true, Dir::FORWARD) {}

Animation::Job::Job(DeltaType duration, JobPtr prev, double progress, bool paused, Dir dir)
  : duration(duration),
    offset(duration * progress),
    dir(dir),
    paused(paused),
    prev(prev) {
  assert(duration > 0);
  assert(progress >= 0);
  assert(progress <= 1);
  if (prev) {
    prev->next.push_back(this);
  }
}

void Animation::Job::first() {
  update(0.0, 0.0);
}

void Animation::Job::last() {
  update(1.0, duration);
}

void Animation::Job::setDuration(DeltaType newDuration) {
  assert(newDuration > 0);
  //preserving progress
  offset = offset / duration * newDuration;
  duration = newDuration;
}

void Animation::Job::setDir(Dir newDir) {
  dir = newDir;
}

void Animation::Job::setProgress(double newProgress) {
  assert(newProgress >= 0);
  assert(newProgress <= 1);
  offset = duration * newProgress;
}

void Animation::Job::setOffset(DeltaType newOffset) {
  assert(newOffset >= 0);
  assert(newOffset <= duration);
  offset = newOffset;
}

void Animation::Job::setPrev(JobPtr newPrev) {
  if (prev) {
    assert(prev->next.size());
    #ifdef DEBUG
    int count = 0;
    START_LOOP:
    #endif
    for (auto i = prev->next.begin(); i != prev->next.end(); ++i) {
      if (*i == this) {
        #ifdef DEBUG
        count++;
        if (i == prev->next.begin()) {
          prev->next.erase(i);
          goto START_LOOP;
        } else {
          prev->next.erase(i);
          --i;
        }
        #else
        prev->next.erase(i);
        break;
        #endif
      }
    }
    #ifdef DEBUG
    assert(count == 1);
    #endif
  }
  prev = newPrev;
  offset = 0;
  paused = true;
}

DeltaType Animation::Job::getDuration() const {
  return duration;
}

Animation::Dir Animation::Job::getDir() const {
  return dir;
}

double Animation::Job::getProgress() const {
  return offset / duration;
}

DeltaType Animation::Job::getOffset() const {
  return offset;
}

Animation::JobPtr Animation::Job::getPrev() const {
  return prev;
}

void Animation::Job::pause() {
  paused = true;
}

void Animation::Job::resume() {
  paused = false;
}

bool Animation::Job::running() const {
  return !paused;
}

void Animation::Job::update(DeltaType delta, int frame) {
  if (paused) {
    called = Called::NONE;
    calledFrame = frame;
  } else if (calledFrame < frame) {
    switch (called) {
      case Called::FIRST:
        if (dir == Dir::FORWARD) {
          stepForward(delta, frame);
        } else {
          paused = true;
        }
        break;
      case Called::LAST:
        if (dir == Dir::BACKWARD) {
          stepBackward(delta, frame);
        } else {
          paused = true;
        }
        break;
      case Called::UPDATE:
        step(delta, frame);
        break;
      case Called::NONE:
        if (!paused) {
          if (offset == 0) {
            first();
            called = Called::FIRST;
            calledFrame = frame;
          } else if (offset == duration) {
            last();
            called = Called::LAST;
            calledFrame = frame;
          } else {
            step(delta, frame);
          }
        }
    }
  }
}

void Animation::Job::step(DeltaType delta, int frame) {
  switch (dir) {
    case Dir::FORWARD:
      stepForward(delta, frame);
      break;
    case Dir::BACKWARD:
      stepBackward(delta, frame);
      break;
  }
}

void Animation::Job::stepForward(DeltaType delta, int frame) {
  if (!paused) {
    offset += delta;
    if (offset >= duration) {
      offset = duration;
      last();
      called = Called::LAST;
      calledFrame = frame;
      
      for (auto i = next.begin(); i != next.end(); ++i) {
        (*i)->paused = false;
        (*i)->first();
        (*i)->called = Called::FIRST;
        (*i)->calledFrame = frame;
      }
    } else {
      update(static_cast<double>(offset) / duration, offset);
      called = Called::UPDATE;
      calledFrame = frame;
    }
  }
}

void Animation::Job::stepBackward(DeltaType delta, int frame) {
  if (!paused) {
    offset -= delta;
    if (offset <= 0) {
      offset = 0;
      first();
      called = Called::FIRST;
      calledFrame = frame;
    } else {
      update(static_cast<double>(offset) / duration, offset);
      called = Called::UPDATE;
      calledFrame = frame;
    }
  }
}

Animation::~Animation() {
  for (auto i = jobs.begin(); i != jobs.end(); ++i) {
    (*i)->prev.reset();
  }
}

void Animation::addJob(JobPtr job) {
  assert(!jobs.count(job));
  if (job->prev) {
    assert(jobs.count(job->prev));
  }
  jobs.insert(job);
}

void Animation::remJob(JobPtr job) {
  jobs.erase(job);
  while (job->next.begin() != job->next.end()) {
    std::shared_ptr<Job> shared(job->next.front(), [](Job *){});
    remJob(shared);
    job->next.pop_front();
  }
}

void Animation::update(DeltaType delta) {
  Profiler p("Animation");
  for (auto i = jobs.begin(); i != jobs.end(); ++i) {
    (*i)->update(delta, frame);
  }
  frame++;
}
