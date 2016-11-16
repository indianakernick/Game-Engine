//
//  escape.hpp
//  game engine
//
//  Created by Indi Kernick on 1/09/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef escape_hpp
#define escape_hpp

#include <string>
#include "../Math/format.hpp"
#include "digitchar.hpp"
#include <cassert>
#include <cstdlib>

namespace Strings {
  std::string escape(const std::string&);
  std::string unescape(const std::string&);
}

#endif
