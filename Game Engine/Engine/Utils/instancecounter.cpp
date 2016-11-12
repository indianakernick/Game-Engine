//
//  instancecounter.cpp
//  game engine
//
//  Created by Indi Kernick on 8/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "instancecounter.hpp"

template <typename T, size_t MAX_COUNT>
size_t InstanceCounter<T, MAX_COUNT>::count = 0;