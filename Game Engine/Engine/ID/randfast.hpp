//
//  randfast.hpp
//  game engine
//
//  Created by Indi Kernick on 11/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef id_randfast_hpp
#define id_randfast_hpp

#include <random>
#include "interface.hpp"

namespace ID {
  class RandFast : public Interface {
  public:
    RandFast() = default;
    
    inline Type create() override {
      return dist(gen);
    };
    inline void remove(Type) override {
      assert(0);
    }
    inline void removeAll() override {
      assert(0);
    }
    inline bool has(Type) override {
      assert(0);
      return false;
    }
    
  private:
    std::default_random_engine gen;
    std::uniform_int_distribution<Type> dist {0, MAX_VAL};
  };
}

#endif