//
//  rand.hpp
//  game engine
//
//  Created by Indi Kernick on 11/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef id_rand_hpp
#define id_rand_hpp

#include <random>
#include <unordered_set>
#include "interface.hpp"

namespace ID {
  class Rand : public Interface {
  public:
    Rand() = default;
    
    Type create() override;
    void remove(Type id) override;
    void removeAll() override;
    bool has(Type id) override;
  private:
    std::default_random_engine gen;
    std::uniform_int_distribution<Type> dist {0, MAX_VAL};
    std::unordered_set<Type> ids;
  };
}

#endif