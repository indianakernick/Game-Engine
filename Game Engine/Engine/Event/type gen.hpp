//
//  type gen.hpp
//  Game Engine
//
//  Created by Indi Kernick on 18/3/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef engine_event_type_gen_hpp
#define engine_event_type_gen_hpp

#include "../ID/global.hpp"
#include "event.hpp"

namespace Game {
  using EvtTypeGen = ID::Global<Event::Type, Event>;
}

#endif
