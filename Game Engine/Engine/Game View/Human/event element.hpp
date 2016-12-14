//
//  event element.hpp
//  Game Engine
//
//  Created by Indi Kernick on 13/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_game_view_human_event_element_hpp
#define engine_game_view_human_event_element_hpp

#include <list>
#include <map>
#include <queue>
#include "event.hpp"

//an element that has event listeners

class EventElement {
public:
  EventElement() = default;
  virtual ~EventElement() = default;
  
protected:
  template <typename EVENT>
  void addEventListener(void (*listener)(const EVENT &)) {
    eventListeners[EVENT::TYPE].push_front(listener);
  }
  template <typename EVENT>
  void remEventListener(void (*listener)(const EVENT &)) {
    eventListeners[EVENT::TYPE].remove(listener);
  }
  
  void pushEvent(Events::Event::Ptr event);
  void dispatchEvents();
private:
  using ListenerList = std::list<void *>;
  using ListenerMap = std::map<Events::Type, ListenerList>;
  ListenerMap eventListeners;
  
  std::queue<Events::Event::Ptr> eventQueue;
  template <typename EVENT>
  bool hasListener() {
    auto listIter = eventListeners.find(EVENT::TYPE);
    if (listIter == eventListeners.end()) {
      return false;
    } else {
      if (listIter->second.empty()) {
        return false;
      } else {
        return true;
      }
    }
  }
  void dispatchEvent(Events::Event::Ptr event);
  
  template <typename EVENT>
  void dispatch(const EVENT &event) {
    using ListenerFunc = void (const EVENT &);
  
    auto listIter = eventListeners.find(EVENT::TYPE);
    if (listIter != eventListeners.end()) {
      ListenerList list = listIter->second;
      for (auto i = list.begin(); i != list.end(); ++i) {
        ListenerFunc *func = reinterpret_cast<ListenerFunc *>(*i);
        func(event);
      }
    }
  }

};

#endif
