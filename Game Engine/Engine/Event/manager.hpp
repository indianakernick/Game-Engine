//
//  manager.hpp
//  Game Engine
//
//  Created by Indi Kernick on 11/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_event_manager_hpp
#define engine_event_manager_hpp

#include "event.hpp"
#include <deque>
#include <unordered_map>
#include <vector>
#include <functional>
#include "../Utils/logger.hpp"
#include "../Time/stopwatch.hpp"
#include "../Utils/profiler.hpp"
#include "../ID/local.hpp"

namespace Game {
  class EventManager {
  public:
    using Listener = std::function<void (const Event::Ptr)>;
    using ListenerID = uint32_t;

    explicit EventManager(uint64_t timeLimit);
    ~EventManager();
    
    ///Call the event listeners for each event. Never takes longer than
    ///timeLimit nanoseconds to process.
    void update();
    
    ///Emit a event
    void emit(Event::Ptr);
    ///Emit a event immediately
    void emitNow(Event::Ptr);
    
    ///Add a event listener
    ListenerID addListener(Event::Type type, const Listener &);
    ///Remove a event listener
    void remListener(Event::Type type, ListenerID);
    
    ///Add a universal event listener. A listener for any event
    ListenerID addListener(const Listener &);
    ///Remove a universal event listener.
    void remListener(ListenerID);
  private:
    std::deque<Event::Ptr> queue[2];
    
    using Listeners = std::unordered_map<ListenerID, Listener>;
    std::unordered_map<Event::Type, Listeners> listeners;
    Listeners anyListeners;
    
    //iterators to listeners that will be removed once all the listeners
    //have been called
    using Iterators = std::vector<Listeners::iterator>;
    std::unordered_map<Event::Type, Iterators> iterators;
    Iterators anyIterators;
    
    std::unordered_map<Event::Type, Listeners> newListeners;
    Listeners anyNewListeners;
    
    uint64_t timeLimit;
    ID::Local<ListenerID> idGen;
    
    uint8_t currentQueue = 0;
    bool iterating = false;
    
    void removeIterators();
    void addListeners();
  };
}

extern std::unique_ptr<Game::EventManager> evtMan;

#endif
