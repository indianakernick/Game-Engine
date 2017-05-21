//
//  observable.hpp
//  Game Engine
//
//  Created by Indi Kernick on 16/5/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_observable_hpp
#define engine_utils_observable_hpp

#include "../ID/local.hpp"
#include <functional>
#include <unordered_map>
#include <vector>
#include <exception>
#include <cassert>
#include "type name.hpp"

template <typename Listener, typename ListenerId = uint32_t>
class Observable;

template <typename ListenerId, typename... CallbackArgs>
class Observable<bool (CallbackArgs...), ListenerId> {
public:
  using Listener = std::function<bool (CallbackArgs...)>;
  using ListenerID = ListenerId;

  class BadListenerID final : public std::exception {
  public:
    BadListenerID(ListenerID id)
      : id(id) {}
    
    ListenerID getID() const {
      return id;
    }
    
    const char *what() const noexcept override {
      return "Observable::remListener was called with a bad ID";
    }
    
  private:
    ListenerID id;
  };

  Observable() = default;
  ~Observable() = default;
  
  bool notify(CallbackArgs... args) {
    assert(!notifying);
    notifying = true;
    
    bool out = true;
    for (auto l = listeners.cbegin(); l != listeners.cend(); l++) {
      out = out && (l->second)(args...);
    }
    
    notifying = false;
    
    addNewListeners();
    remOldListeners();
    
    return out;
  }
  
  ListenerID addListener(const Listener &listener) {
    assert(listener);
    
    const ListenerID id = idGen.make();
    if (notifying) {
      newListeners.emplace(id, listener);
    } else {
      listeners.emplace(id, listener);
    }
    return id;
  }
  
  void remListener(ListenerID id) {
    if (notifying) {
      Iterator iter = listeners.find(id);
      if (iter != listeners.end()) {
        oldListeners.push_back(iter);
        return;
      }
    } else {
      if (listeners.erase(id)) {
        return;
      }
    }
    
    throw BadListenerID(id);
  }
  
private:
  using Listeners = std::unordered_map<ListenerID, Listener>;
  using Iterator = typename Listeners::iterator;
  using Iterators = std::vector<Iterator>;
  Listeners listeners;
  //Listeners that will be added after notify finishes
  Listeners newListeners;
  //listeners that will be removed after notify finishes
  Iterators oldListeners;
  ID::Local<ListenerID> idGen;
  //notify is currently running
  bool notifying = false;
  
  void addNewListeners() {
    assert(!notifying);
    
    //listeners.merge(oldListeners);
    listeners.insert(newListeners.cbegin(), newListeners.cend());
    oldListeners.clear();
  }
  void remOldListeners() {
    assert(!notifying);
    
    for (auto l = oldListeners.cbegin(); l != oldListeners.cend(); l++) {
      listeners.erase(*l);
    }
    oldListeners.clear();
  }
};

#endif
