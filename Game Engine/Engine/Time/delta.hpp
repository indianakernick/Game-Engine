//
//  delta.hpp
//  Game Engine
//
//  Created by Indi Kernick on 22/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef delta_hpp
#define delta_hpp

#include "get.hpp"

namespace Time {
  class Delta {
  public:
    explicit Delta(Unit = SEC);
    
    ///Get the amount of time that has passed since you last called this function
    double get();
  private:
    const Unit unit;
    double lastTime;
  };
}

#endif
