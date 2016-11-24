//
//  machine.hpp
//  Game Engine
//
//  Created by Indi Kernick on 18/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef machine_hpp
#define machine_hpp

#include <assert.h>
#include "state.hpp"

namespace FSM {
  class Machine {
  public:
    Machine(State* initial);
    virtual ~Machine();
    
    void update();
  private:
    State* state {nullptr};
  };
}

#endif
