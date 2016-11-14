//
//  time.hpp
//  Game Engine
//
//  Created by Indi Kernick on 14/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef time_hpp
#define time_hpp

#include <chrono>
#include "Math/siconstants.hpp"

namespace Time {
  uint64_t getNano();
  double getMilli();
  double getSec();
};

#endif
