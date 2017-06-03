//
//  manager.hpp
//  Game Engine
//
//  Created by Indi Kernick on 11/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_event_manager_hpp
#define engine_event_manager_hpp

#include <deque>
#include "event.hpp"
#include "type gen.hpp"
#include "../Utils/logger.hpp"
#include "../Utils/profiler.hpp"
#include "../Utils/dispatcher.hpp"
#include "../Time/stopwatch.hpp"

namespace Game {
  class EventManager {
  private:
    using DispatcherImpl = GroupDispatcher<void (const Event::Ptr), void, Event::Type, uint32_t>;
    
  public:
    using Listener = DispatcherImpl::Listener;
    using ListenerID = DispatcherImpl::ListenerID;

    explicit EventManager(uint64_t);
    ~EventManager() = default;
    
    ///Call the event listeners for each event. Never takes longer than
    ///timeLimit nanoseconds to process.
    void update();
    
    ///Emit a event
    void emit(Event::Ptr);
    ///Emit a event immediately
    void emitNow(Event::Ptr);
    
    ///Add a event listener
    ListenerID addListener(Event::Type, const Listener &);
    ///Remove a event listener
    void remListener(ListenerID);
    
    ///Add a universal event listener. A listener for any event
    ListenerID addAnyListener(const Listener &);
    
  private:
    //the type of an event listener listening to any event
    static const Event::Type ANY_TYPE;
  
    DispatcherImpl dispatcher;
    std::deque<Event::Ptr> queue[2];
    uint64_t timeLimit;
    uint8_t currentQueue = 0;
  };
}

extern std::unique_ptr<Game::EventManager> evtMan;

#endif
