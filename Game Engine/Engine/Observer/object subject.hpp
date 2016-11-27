//
//  object subject.hpp
//  Game Engine
//
//  Created by Indi Kernick on 27/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef object_subject_hpp
#define object_subject_hpp

#include <set>
#include <memory>
#include <cassert>
#include "object.hpp"

namespace Observer {
  template <typename EVENT>
  class Subject {
  public:
    //i would normally put this in Observer but it would be a dependant type
    //so i'd have to prepend typename and thats just annoying
    using ObserverPtr = std::shared_ptr<Observer<EVENT>>;

    Subject() = default;
    virtual ~Subject() = default;
    
    void addObserver(ObserverPtr observer) {
      assert(observer);
      observers.insert(observer);
    }
    void remObserver(ObserverPtr observer) {
      assert(observer);
      observers.erase(observer);
    }
  protected:
    void dispatch(EVENT event) {
      for (auto i = observers.begin(); i != observers.end(); ++i) {
        (*i)->receiveEvent(event);
      }
    }
    void dispatch(ObserverPtr observer, EVENT event) {
      assert(observer);
      assert(observers.count(observer));
      observer->receiveEvent(event);
    }
  private:
    std::set<ObserverPtr> observers;
  };
}

#endif
