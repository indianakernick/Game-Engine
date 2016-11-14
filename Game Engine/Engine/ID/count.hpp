//
//  count.hpp
//  game engine
//
//  Created by Indi Kernick on 11/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef id_count_hpp
#define id_count_hpp

#include "interface.hpp"
#include <unordered_set>

namespace ID {
  class Count : public Interface {
  public:
    Count() = default;
    
    Type create() override;
    void remove(Type id) override;
    void removeAll() override;
    bool has(Type id) override;
  private:
    std::unordered_set<Type> ids;
    Type count = MAX_VAL;
  };
}

#endif