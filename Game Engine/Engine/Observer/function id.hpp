//
//  function id.hpp
//  Game Engine
//
//  Created by Indi Kernick on 27/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_observer_function_id_hpp
#define engine_observer_function_id_hpp

#include <functional>
#include <map>
#include "../ID/rand.hpp"

namespace Observer {
  template <typename DATA>
  class SubjectID {
  public:
    using Observer = std::function<void (DATA)>;
    
    ID::Type addObserver(Observer ob) {
      ID::Type id = idGen.create();
      observers[id] = ob;
      return id;
    }
    void remObserver(ID::Type id) {
      observers.erase(id);
      idGen.remove(id);
    }
  protected:
    void dispatch(DATA data) {
      for (auto i = observers.begin(); i != observers.end(); ++i) {
        i->second(data);
      }
    }
  private:
    std::map<ID::Type, Observer> observers;
    ID::Rand idGen;
  };
}

#endif
