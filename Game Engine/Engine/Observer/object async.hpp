//
//  object async.hpp
//  Game Engine
//
//  Created by Indi Kernick on 27/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef object_async_hpp
#define object_async_hpp

#include <queue>
#include "object.hpp"

namespace Observer {
  template <typename EVENT>
  class ASyncObserver : public Observer<EVENT> {
  friend class Subject<EVENT>;
  public:
    ASyncObserver() = default;
    virtual ~ASyncObserver() = default;
    
  protected:
    virtual void handleEvent(const EVENT &) override = 0;
    size_t dispatchEvents(size_t num = UINTMAX_MAX) {
      size_t disptachedNum = 0;
      while (num-- && !events.empty()) {
        handleEvent(events.front());
        events.pop();
        disptachedNum++;
      }
      return disptachedNum;
    }
  private:
    std::queue<EVENT> events;
    void receiveEvent(const EVENT &e) override {
      events.emplace(e);
    }
  };
}

#endif
