//
//  eventmanager.hpp
//  game engine
//
//  Created by Indi Kernick on 11/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef eventmanager_hpp
#define eventmanager_hpp

#include <functional>
#include "event.hpp"
#include <memory>
#include <map>
#include <list>
#include <queue>
#include "task.hpp"
#include <iostream>

#ifdef DEBUG
#include "logger.hpp"
#endif

using EventPtr = std::shared_ptr<Event>;

class EventManager : public Task {
public:
  using Listener = std::function<void (EventPtr)>;
  EventManager();
  
  void addListener(Event::Type, Listener);
  void remListener(Event::Type, Listener);
  ///Calls the listeners immediately
  void triggerNow(EventPtr);
  ///Calls the listeners on the next frame
  void triggerLater(EventPtr);
  
private:
  typedef std::queue<EventPtr> EventQueue;
  typedef std::list<Listener> ListenerList;
  typedef std::map<Event::Type, ListenerList> ListenerMap;
  
  EventQueue queues[2];
  ListenerMap listeners;
  uint8_t activeQueue = 0;
  #ifdef DEBUG
  Logger logger;
  #endif
  
  void update(double) override;
  
  static bool compare(Listener, Listener);
};

#endif