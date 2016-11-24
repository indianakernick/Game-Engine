//
//  eventin.hpp
//  Game Engine
//
//  Created by Indi Kernick on 2/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef eventin_hpp
#define eventin_hpp

#include <functional>
#include <vector>
#include <map>
#include <ID/rand.hpp>

namespace EventSystem {
  template<typename EVENT, typename IN_DATA>
  class In {
  private:
    struct Callback {
      std::function<void (IN_DATA)> func;
      bool removed = false;
    };
  public:
    class ListenerID {
    friend class In;
    public:
      ListenerID() = default;
    private:
      ::ID::Type sysID;
      typename std::vector<Callback>::iterator callback;
    };
    
    In() : id(ID.create()) {}
    
    ListenerID addListener(EVENT event, std::function<void (IN_DATA)> callback) {
      Callbacks& callbacks = getCallbacks(event);
      callbacks.push_back({callback});
      ListenerID id;
      id.sysID = this->id;
      id.callback = --callbacks.end();
      return id;
    }
    
    void removeListener(ListenerID id) {
      if (id.sysID == this->id) {
        id.callback->removed = true;
      }
    }
  protected:
    void dispatch(EVENT event, IN_DATA in) {
      auto iter = listeners.find(event);
      if (iter != listeners.end()) {
        for (auto i = iter->second.begin(); i != iter->second.end(); ++i) {
          if (!i->removed) {
            i->func(in);
          }
        }
      }
    }
  private:
    typedef std::vector<Callback> Callbacks;
    typedef std::map<EVENT, Callbacks> Listeners;
    Listeners listeners;
    
    Callbacks& getCallbacks(EVENT event) {
      auto iter = listeners.find(event);
      if (iter != listeners.end()) {
        return iter->second;
      } else {
        listeners[event] = {};
        return listeners.find(event)->second;
      }
    }
    
    ::ID::Type id;
    static ::ID::Rand ID;
  };
}

template<typename EVENT, typename IN_DATA>
::ID::Rand EventSystem::In<EVENT, IN_DATA>::ID;

#endif
