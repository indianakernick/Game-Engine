//
//  library factory.hpp
//  Game Engine
//
//  Created by Indi Kernick on 16/12/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_application_library_factory_hpp
#define engine_application_library_factory_hpp

#include "library.hpp"
#include "Libraries/sdl.hpp"

namespace Libraries {
  Library::Ptr make();
};

#endif
