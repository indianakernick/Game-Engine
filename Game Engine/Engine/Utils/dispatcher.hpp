//
//  dispatcher.hpp
//  Game Engine
//
//  Created by Indi Kernick on 16/5/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_utils_dispatcher_hpp
#define engine_utils_dispatcher_hpp

#include <functional>
#include <vector>
#include <exception>
#include <cassert>

template <typename Listener, typename ListenerId = uint32_t>
class Dispatcher;

template <typename ListenerId, typename ListenerRet, typename ...ListenerArgs>
class Dispatcher<ListenerRet(ListenerArgs...), ListenerId> {
public:
  using Listener = std::function<ListenerRet (ListenerArgs...)>;
  using ListenerID = ListenerId;
  using Listeners = std::vector<Listener>;
  
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
    
    listeners.emplace_back(listener);
    return static_cast<ListenerID>(listeners.size() - 1);
  }
  
  void remListener(ListenerID id) {
    if (id >= listeners.size()) {
      throw BadListenerID(id);
    }
    
    if (dispatching) {
      oldListeners.push_back(id);
    } else {
      listeners[id] = nullListener;
    }
  }

protected:
  ListenerRet dispatch(ListenerArgs... args) {
    assert(!dispatching);
    
    dispatching = true;
    
    if constexpr (std::is_void<ListenerRet>::value) {
      dispatchImpl(listeners, args...);
      dispatching = false;
      remOldListeners();
    } else {
      const ListenerRet out = dispatchImpl(listeners, args...);
      dispatching = false;
      remOldListeners();
      
      return out;
    }
  }
  
private:
  Listeners listeners;
  //listeners that will be removed after dispatch finishes
  std::vector<ListenerID> oldListeners;
  //dispatch is currently running
  bool dispatching = false;
  
  void remOldListeners() {
    assert(!dispatching);
    
    for (auto l = oldListeners.cbegin(); l != oldListeners.cend(); ++l) {
      listeners[*l] = nullListener;
    }
    oldListeners.clear();
  }
  
  static ListenerRet nullListener(ListenerArgs...) {
    if constexpr (!std::is_void<ListenerRet>::value) {
      return {};
    }
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
    const auto end = listeners.cend();
    for (auto l = listeners.cbegin(); l != end; ++l) {
      (*l)(args...);
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
    const auto end = listeners.cend();
    for (auto l = listeners.cbegin(); l != end; ++l) {
      out = out && (*l)(args...);
    }
    return out;
  }
};

#endif
