//
//  function.hpp
//  Game Engine
//
//  Created by Indi Kernick on 27/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef function_hpp
#define function_hpp

#include <functional>
#include <set>

namespace Observer {
  template <typename DATA>
  class SubjectFunc {
  public:
    //i would normally use std::function instead of function pointers
    //but i cant get std::function::target to work
    using Observer = void(*)(DATA);
    
    SubjectFunc() = default;
    virtual ~SubjectFunc() = default;
    
    void addObserver(Observer ob) {
      observers.insert(ob);
    }
    void remObserver(Observer ob) {
      observers.erase(ob);
    }
  protected:
    void dispatch(DATA data) {
      for (auto i = observers.begin(); i != observers.end(); ++i) {
        (*i)(data);
      }
    }
  private:
    std::set<Observer> observers;
  };
}

#endif
