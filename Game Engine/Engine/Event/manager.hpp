//
//  manager.hpp
//  Game Engine
//
//  Created by Indi Kernick on 11/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_event_manager_hpp
#define engine_event_manager_hpp

#include <functional>
#include "event.hpp"
#include <unordered_map>
#include <list>
#include <queue>
#include "../Utils/logger.hpp"

namespace Game {
  class EventManager {
  public:
    using Listener = std::function<void (Event::Ptr)>;
    
    EventManager() = delete;
    ~EventManager() = delete;
    
    static void update();
    
    ///Adds a listener to be called when an event is fired
    static void addListener(Event::Type, const Listener &);
    ///Returns true if listener was actually removed
    static bool remListener(Event::Type, const Listener &);
    ///Calls the listeners immediately
    static void triggerNow(Event::Ptr);
    ///Calls the listeners on the next frame
    static void trigger(Event::Ptr);
    
  private:
    using EventQueue = std::queue<Event::Ptr>;
    using ListenerList = std::list<Listener>;
    using ListenerMap = std::unordered_map<Event::Type, ListenerList>;
    
    static EventQueue queues[2];
    static ListenerMap listeners;
    static uint8_t activeQueue;
    
    static bool compare(const Listener &, const Listener &);
  };
}

#endif
