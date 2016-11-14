//
//  interface.cpp
//  game engine
//
//  Created by Indi Kernick on 11/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "interface.hpp"

std::string ID::display(Type id) {
  return Math::Format::hexPad64(id);
}