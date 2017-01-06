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
#include <map>
#include <list>
#include <queue>
#include "../Task Manager/task.hpp"
#include "../Utils/debug.hpp"

#ifdef DEBUG
#include "../Utils/logger.hpp"
#endif

namespace Game {
  class EventManager : public Task {
  public:
    using Ptr = std::shared_ptr<EventManager>;
    using Listener = std::function<void (Event::Ptr)>;
    
    EventManager() = default;
    
    ///Adds a listener to be called when an event is fired
    void addListener(Event::Type, const Listener &);
    ///Returns true if listener was actually removed
    bool remListener(Event::Type, const Listener &);
    ///Calls the listeners immediately
    void triggerNow(Event::Ptr);
    ///Calls the listeners on the next frame
    void trigger(Event::Ptr);
    
  private:
    using EventQueue = std::queue<Event::Ptr>;
    using ListenerList = std::list<Listener>;
    using ListenerMap = std::map<Event::Type, ListenerList>;
    
    EventQueue queues[2];
    ListenerMap listeners;
    uint8_t activeQueue = 0;
    
    void update(Task::Delta) override;
    
    static bool compare(const Listener &, const Listener &);
  };
}

#endif
