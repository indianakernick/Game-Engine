//
//  any.cpp
//  Game Engine
//
//  Created by Indi Kernick on 25/1/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "any.hpp"

size_t std::hash<Any>::operator()(const Any &any) const {
  return any.deleter->getValHash();
};
