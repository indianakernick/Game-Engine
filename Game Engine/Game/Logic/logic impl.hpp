//
//  logic impl.hpp
//  Game Engine
//
//  Created by Indi Kernick on 24/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef game_logic_impl_hpp
#define game_logic_impl_hpp

#include "../../Engine/Game Logic/base.hpp"
#include <vector>

namespace Game {
  class LogicImpl final : public Logic {
  public:
    LogicImpl() = default;
    ~LogicImpl() = default;
    
  private:
    std::vector<Actor::Ptr> actors;
  };
}

#endif
