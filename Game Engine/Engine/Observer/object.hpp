//
//  object.hpp
//  Game Engine
//
//  Created by Indi Kernick on 27/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef object_hpp
#define object_hpp

namespace Observer {
  template <typename EVENT>
  class Subject;

  template <typename EVENT>
  class Observer {
  friend class Subject<EVENT>;
  public:
    Observer() = default;
    virtual ~Observer() = default;
    
  protected:
    virtual void handleEvent(const EVENT &) = 0;
  private:
    virtual void receiveEvent(const EVENT &) = 0;
  };
}

#endif
