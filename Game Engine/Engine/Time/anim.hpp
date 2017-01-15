//
//  anim.hpp
//  Game Engine
//
//  Created by Indi Kernick on 2/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef anim_hpp
#define anim_hpp

#include "get.hpp"
#include "../Math/interpolate.hpp"
#include "../Math/clamp.hpp"
#include <cassert>
#include <iostream>

namespace Time {
  //i had these in the Anim class but the names were too long because you have
  //to include the template parameters (because the class is incomplete without
  //them) even though these enums aren't directly dependant on the template
  //parameters
  
  enum class AnimEdgeMode : char {
    ///continue past the edge
    NOTHING,
    ///return to the beginning and continue
    REPEAT,
    ///pause on the edge
    PAUSE,
    ///reset
    STOP,
    ///"bounce" off the edge
    CHANGE_DIR
  };
  enum class AnimDir : char {
    FORWARD,
    BACKWARD
  };
  
  template <typename DURATION_TYPE>
  class Anim {
  private:
    enum State : char {
      RUNNING,
      STOPPED,
      PAUSED
    };
  
  public:
    Anim(uint64_t duration, AnimEdgeMode edgeMode = AnimEdgeMode::REPEAT)
      : duration(duration), edgeMode(edgeMode) {}
    
    ///Start the animation
    void start() {
      assert(state == STOPPED);
      state = RUNNING;
      startPoint = getI<DURATION_TYPE>();
    }
    ///Stop the animation, return the playhead to the beginning and the dir
    ///to FORWARD
    void stop() {
      assert(state == RUNNING);
      state = STOPPED;
      dir = AnimDir::FORWARD;
    }
    ///Pause the animation to be resumed later
    void pause() {
      assert(state == RUNNING);
      pauseHelper(getI<DURATION_TYPE>());
    }
    ///Resume the animation after it was paused
    void resume() {
      assert(state == PAUSED);
      state = RUNNING;
      startPoint += getI<DURATION_TYPE>() - pausePoint;
    }
    
    void setDir(AnimDir newDir) {
      dir = newDir;
    }
    
    void flipDir() {
      dir = static_cast<AnimDir>(1 - static_cast<char>(dir));
    }
    
    AnimDir getDir() {
      return dir;
    }
    
    void setDuration(uint64_t newDuration) {
      duration = newDuration;
    }
    
    uint64_t getDuration() {
      return duration;
    }
    
    void setEdgeMode(AnimEdgeMode newEdgeMode) {
      edgeMode = newEdgeMode;
    }
    
    AnimEdgeMode getEdgeMode() {
      return edgeMode;
    }
    
    bool isRunning() {
      return state == RUNNING;
    }
    
    bool isStopped() {
      return state == STOPPED;
    }
    
    bool isPaused() {
      return state == PAUSED;
    }
    
    void setProgress(double newProgress) {
      setProgressHelper(newProgress, getI<DURATION_TYPE>());
    }
    
    double getProgress() {
      uint64_t now = getI<DURATION_TYPE>();
      
      if (state == STOPPED) {
        return 0.0;
      } else if (state == PAUSED) {
        startPoint += now - pausePoint;
        pausePoint = now;
        return getProgressHelper(now);
      }
      
      double progress = getProgressHelper(now);
      
      if (now < startPoint || now > startPoint + duration) {
        return handleEdges(progress, now);
      } else {
        return progress;
      }
    }
  private:
    uint64_t duration;
    uint64_t startPoint;
    uint64_t pausePoint;
    AnimEdgeMode edgeMode;
    State state = STOPPED;
    AnimDir dir = AnimDir::FORWARD;
    
    void setProgressHelper(double newProgress, uint64_t now) {
      if (dir == AnimDir::FORWARD) {
        startPoint = now - newProgress * duration;
      } else {
        startPoint = now + newProgress * duration - duration;
      }
    }
    
    void pauseHelper(uint64_t now) {
      state = PAUSED;
      pausePoint = now;
    }
    
    double getProgressHelper(uint64_t now) {
      if (dir == AnimDir::FORWARD) {
        return Math::invLerp<double>(now, startPoint, startPoint + duration);
      } else {
        return Math::invLerp<double>(now, startPoint + duration, startPoint);
      }
    }
    
    double handleEdges(double progress, uint64_t now) {
      double newProgress;
      switch (edgeMode) {
        case AnimEdgeMode::NOTHING:
          newProgress = progress;
          break;
        case AnimEdgeMode::REPEAT:
          newProgress = Math::norm(progress);
          break;
        case AnimEdgeMode::PAUSE:
          pauseHelper(now);
          newProgress = Math::clamp(progress, 0.0, 1.0);
          break;
        case AnimEdgeMode::STOP:
          stop();
          newProgress = 0.0;
          break;
        case AnimEdgeMode::CHANGE_DIR:
          newProgress = progress;
          do {
            if (dir == AnimDir::FORWARD) {
              newProgress = 1 - (newProgress - 1);
              dir = AnimDir::BACKWARD;
            } else {
              newProgress = -newProgress;
              dir = AnimDir::FORWARD;
            }
          } while (newProgress < 0.0 || newProgress > 1.0);
          break;
      }
      setProgressHelper(newProgress, now);
      return newProgress;
    }
  };
};

#endif
