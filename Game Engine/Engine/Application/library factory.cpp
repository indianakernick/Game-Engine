//
//  library factory.cpp
//  Game Engine
//
//  Created by Indi Kernick on 16/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "library factory.hpp"

#ifdef _SDL_H

Library::Ptr Libraries::make() {
  return std::make_shared<Libraries::SDL>();
}

#endif
