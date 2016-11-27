//
//  object sync.hpp
//  Game Engine
//
//  Created by Indi Kernick on 27/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef object_sync_hpp
#define object_sync_hpp

#include "object.hpp"

namespace Observer {
  template <typename EVENT>
  class SyncObserver : public Observer<EVENT> {
  friend class Subject<EVENT>;
  public:
    SyncObserver() = default;
    virtual ~SyncObserver() = default;
    
  protected:
    virtual void handleEvent(EVENT &) override = 0;
  private:
    void receiveEvent(EVENT e) override {
      handleEvent(e);
    }
  };
}

#endif
