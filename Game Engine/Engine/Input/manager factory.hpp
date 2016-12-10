//
//  manager factory.hpp
//  Game Engine
//
//  Created by Indi Kernick on 5/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_input_manager_factory_hpp
#define engine_input_manager_factory_hpp

#include "manager.hpp"
//these headers have an #ifdef for the library they use so
//including implementations that we aren't using is fine
#include "Managers/sdl.hpp"

namespace Input {
  Manager::Ptr makeManager();
}

#endif
