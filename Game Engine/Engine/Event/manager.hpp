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
#include <queue>
#include <vector>
#include <unordered_map>
#include <functional>
#include "../Utils/logger.hpp"
#include "../Time/stopwatch.hpp"
#include "../Utils/profiler.hpp"

namespace Game {
  class EventManager {
  public:
    using Listener = std::function<void (const Event::Ptr)>;

    explicit EventManager(uint64_t timeLimit);
    ~EventManager() = default;
    
    ///Call the event listeners for each event. Never takes longer than
    ///timeLimit nanoseconds to process.
    void update();
    
    ///Emit a event
    void emit(Event::Ptr);
    ///Emit a event immediately
    void emitNow(Event::Ptr);
    
    ///Add a event listener
    void addListener(Event::Type type, const Listener &);
    ///Remove a event listener
    void remListener(Event::Type type, const Listener &);
    
    ///Add a universal event listener. A listener for any event
    void addListener(const Listener &);
    ///Remove a universal event listener.
    void remListener(const Listener &);
  private:
    std::queue<Event::Ptr> queue;
    //it's unlikly that a listener will need to be removed once added
    //so removing a listener doesn't need to be very efficient
    using Listeners = std::vector<Listener>;
    std::unordered_map<Event::Type, Listeners> listeners;
    Listeners anyListeners;
    
    uint64_t timeLimit;
  };
}

template <>
struct std::equal_to<Game::EventManager::Listener> {
  bool operator()(const Game::EventManager::Listener &,
                  const Game::EventManager::Listener &) const;
};

extern std::unique_ptr<Game::EventManager> evtMan;

#endif
