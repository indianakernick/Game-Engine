//
//  library factory.cpp
//  Game Engine
//
//  Created by Indi Kernick on 16/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "library factory.hpp"

#ifdef USE_SDL

Library::Ptr Libraries::make() {
  return std::make_shared<Libraries::SDL>();
}

#else

#error No implementation was found

#endif
