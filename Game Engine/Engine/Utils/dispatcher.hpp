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
#include <stdexcept>
#include <cassert>

/*
RetHandler is a type with an interface compatible with the following

struct RetHandler {
  RetHandler();
  
  void handleReturnValue(ListenerRet);
  ListenerRet getFinalReturnValue();
}
*/

template <typename Listener, typename RetHandler, typename ListenerId = uint32_t>
class Dispatcher;

template <typename ListenerId, typename RetHandler, typename ListenerRet, typename ...ListenerArgs>
class Dispatcher<ListenerRet(ListenerArgs...), RetHandler, ListenerId> {
public:
  using Listener = std::function<ListenerRet (ListenerArgs...)>;
  using ListenerID = ListenerId;
  
  class BadListenerID final : public std::runtime_error {
  public:
    explicit BadListenerID(ListenerID id)
      : std::runtime_error("Dispatcher::remListener was called with a bad ID"), id(id) {}
    
    ListenerID getID() const {
      return id;
    }
    
  private:
    ListenerID id;
  };
  
  class BadListener final : public std::runtime_error {
  public:
    BadListener()
      : std::runtime_error("Dispatcher::addListener was called with a null listener") {}
  };
  
  class BadDispatchCall final : public std::logic_error {
  public:
    BadDispatchCall()
      : std::logic_error("Dispatcher::dispatch was called from an listener") {}
  };

  Dispatcher() = default;
  ~Dispatcher() = default;
  
  ListenerID addListener(const Listener &listener) {
    if (listener == nullptr) {
      throw BadListener();
    }
    
    const ListenerID id = static_cast<ListenerID>(listeners.size());
    listeners.emplace_back(listener);
    return id;
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

  ListenerRet dispatch(ListenerArgs... args) {
    if (dispatching) {
      throw BadDispatchCall();
    }
    
    dispatching = true;
    
    if constexpr (std::is_void<ListenerRet>::value) {
      const auto end = listeners.cend();
      for (auto l = listeners.cbegin(); l != end; ++l) {
        (*l)(args...);
      }
      dispatching = false;
      remOldListeners();
    } else {
      RetHandler retHandler;
      const auto end = listeners.cend();
      for (auto l = listeners.cbegin(); l != end; ++l) {
        retHandler.handleReturnValue((*l)(args...));
      }
      dispatching = false;
      remOldListeners();
      
      return retHandler.getFinalReturnValue();
    }
  }
  
private:
  std::vector<Listener> listeners;
  //listeners that will be removed after dispatch finishes
  std::vector<ListenerID> oldListeners;
  //dispatch is currently running
  bool dispatching = false;
  
  void remOldListeners() {
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
};

///An action that can be observed
template <typename ListenerID, typename ...Args>
using Observable = Dispatcher<void (Args...), void, ListenerID>;

class ConfirmableRetHandler {
public:
  ConfirmableRetHandler() = default;
  ~ConfirmableRetHandler() = default;
  
  void handleReturnValue(const bool val) {
    out = out && val;
  }
  
  bool getFinalReturnValue() const {
    return out;
  }

private:
  bool out = true;
};

///An action that can be confirmed to happen
template <typename ListenerID, typename ...Args>
using Confirmable = Dispatcher<bool (Args...), ConfirmableRetHandler, ListenerID>;

#endif
