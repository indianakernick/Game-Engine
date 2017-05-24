//
//  dispatcher.hpp
//  Game Engine
//
//  Created by Indi Kernick on 16/5/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_dispatcher_hpp
#define engine_utils_dispatcher_hpp

#include "../ID/local.hpp"
#include <functional>
#include <unordered_map>
#include <vector>
#include <exception>
#include <cassert>
#include "type name.hpp"


template <typename Listener, typename ListenerId = uint32_t>
class Dispatcher;

template <typename ListenerId, typename ListenerRet, typename ...ListenerArgs>
class Dispatcher<ListenerRet(ListenerArgs...), ListenerId> {
public:
  using Listener = std::function<ListenerRet (ListenerArgs...)>;
  using ListenerID = ListenerId;
  using Listeners = std::unordered_map<ListenerID, Listener>;
  
  class BadListenerID final : public std::exception {
  public:
    explicit BadListenerID(ListenerID id)
      : id(id) {}
    
    ListenerID getID() const {
      return id;
    }
    
    const char *what() const noexcept override {
      return "Dispatcher::remListener was called with a bad ID";
    }
    
  private:
    ListenerID id;
  };

  Dispatcher() = default;
  virtual ~Dispatcher() = default;
  
  ListenerID addListener(const Listener &listener) {
    assert(listener);
    
    const ListenerID id = idGen.make();
    if (dispatching) {
      newListeners.emplace(id, listener);
    } else {
      listeners.emplace(id, listener);
    }
    return id;
  }
  
  void remListener(ListenerID id) {
    if (dispatching) {
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

protected:
  ListenerRet dispatch(ListenerArgs... args) {
    assert(!dispatching);
    dispatching = true;
    
    if constexpr (std::is_void<ListenerRet>::value) {
      dispatchImpl(listeners, args...);
      
      dispatching = false;
      
      addNewListeners();
      remOldListeners();
    } else {
      const ListenerRet out = dispatchImpl(listeners, args...);
      
      dispatching = false;
      
      addNewListeners();
      remOldListeners();
      
      return out;
    }
  }
  
private:
  using Iterator = typename Listeners::iterator;
  using Iterators = std::vector<Iterator>;
  Listeners listeners;
  //Listeners that will be added after dispatch finishes
  Listeners newListeners;
  //listeners that will be removed after dispatch finishes
  Iterators oldListeners;
  ID::Local<ListenerID> idGen;
  //dispatch is currently running
  bool dispatching = false;
  
  void addNewListeners() {
    assert(!dispatching);
    
    //listeners.merge(oldListeners);
    listeners.insert(newListeners.cbegin(), newListeners.cend());
    oldListeners.clear();
  }
  
  void remOldListeners() {
    assert(!dispatching);
    
    for (auto l = oldListeners.cbegin(); l != oldListeners.cend(); l++) {
      listeners.erase(*l);
    }
    oldListeners.clear();
  }
  
  virtual ListenerRet dispatchImpl(const Listeners &, ListenerArgs...) const = 0;
};

///An action that can be observed
template <typename ...Args>
class Observable : public Dispatcher<void (Args...)> {
public:
  void notify(Args... args) {
    //why is this-> necessary?
    this->dispatch(args...);
  }
  
private:
  using Listeners = typename Dispatcher<void (Args...)>::Listeners;
  void dispatchImpl(const Listeners &listeners, Args... args) const {
    for (auto l = listeners.cbegin(); l != listeners.cend(); l++) {
      (l->second)(args...);
    }
  }
};

///An action that can be confirmed to happen
template <typename ...Args>
class Confirmable : public Dispatcher<bool (Args...)> {
public:
  bool confirm(Args... args) {
    //why is this-> necessary?
    return this->dispatch(args...);
  }

private:
  using Listeners = typename Dispatcher<bool (Args...)>::Listeners;
  bool dispatchImpl(const Listeners &listeners, Args... args) const {
    bool out = true;
    for (auto l = listeners.cbegin(); l != listeners.cend(); l++) {
      out = out && (l->second)(args...);
    }
    return out;
  }
};

#endif
