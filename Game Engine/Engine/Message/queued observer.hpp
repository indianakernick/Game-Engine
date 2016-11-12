//
//  queued observer.hpp
//  game engine
//
//  Created by Indi Kernick on 4/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef queued_observer_hpp
#define queued_observer_hpp

#include <queue>
#include <set>
#include <memory>
#include "profiler.hpp"

template <typename EVENT>
class Observer;

template <typename EVENT>
class Subject {
public:
  Subject() = default;
  virtual ~Subject() = default;
  
  void addObserver(std::shared_ptr<Observer<EVENT>> observer) {
    assert(observer);
    observers.insert(observer);
  }
  void remObserver(std::shared_ptr<Observer<EVENT>> observer) {
    assert(observer);
    observers.erase(observer);
  }
protected:
  void notify(EVENT event) {
    Profiler p("Subject::notify");
    for (auto i = observers.begin(); i != observers.end(); ++i) {
      (*i)->receiveEvent(event);
    }
  }
  void notify(std::shared_ptr<Observer<EVENT>> observer, EVENT event) {
    assert(observer);
    assert(observers.count(observer));
    observer->receiveEvent(event);
  }
private:
  std::set<std::shared_ptr<Observer<EVENT>>> observers;
};

template <typename EVENT>
class Observer {
friend class Subject<EVENT>;
public:
  Observer() = default;
  virtual ~Observer() = default;
  
protected:
  virtual void handleEvent(EVENT &) = 0;
private:
  virtual void receiveEvent(EVENT) = 0;
};

template <typename EVENT>
class ASyncObserver : public Observer<EVENT> {
friend class Subject<EVENT>;
public:
  ASyncObserver() = default;
  virtual ~ASyncObserver() = default;
  
protected:
  virtual void handleEvent(EVENT &) override = 0;
  size_t dispatchEvents(size_t num = UINTMAX_MAX) {
    Profiler p("ASyncObserver::dispatchEvents");
    size_t actualNum = 0;
    while (num-- && !events.empty()) {
      handleEvent(events.front());
      events.pop();
      actualNum++;
    }
    return actualNum;
  }
private:
  std::queue<EVENT> events;
  void receiveEvent(EVENT e) override {
    events.push(e);
  }
};

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


#endif