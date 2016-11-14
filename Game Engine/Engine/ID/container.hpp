//
//  container.hpp
//  ID
//
//  Created by Indi Kernick on 4/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef container_hpp
#define container_hpp

#include "interface.hpp"
#include <unordered_map>
#include <type_traits>
#include <functional>

namespace ID {
  template <typename ID_GEN, typename DATA>
  class Container {
  public:
    Container(std::function<void (DATA)> deleter = [](DATA){})
      : deleter(deleter) {
      static_assert(std::is_base_of<Interface, ID_GEN>::value, "ID_GEN must implement ID::Interface");
    }
    
    Type addItem(DATA item) {
      Type id = gen.create();
      items[id] = item;
      return id;
    }
    
    void remItem(Type id) {
      auto iter = items.find(id);
      if (iter != items.end()) {
        deleter(iter->second);
        items.erase(iter);
      } else {
        throw std::runtime_error("Tried to remove an item but an item with the ID was not found");
      }
    }
    
    DATA &getItem(Type id) {
      auto iter = items.find(id);
      if (iter != items.end()) {
        return iter->second;
      } else {
        throw std::runtime_error("Tried to get an item but an item with the ID was not found");
      }
    }
    
    bool hasItem(Type id) {
      return items.find(id) != items.end();
    }
    
  private:
    std::unordered_map<Type, DATA> items;
    ID_GEN gen;
    std::function<void (DATA)> deleter;
  };
}

#endif