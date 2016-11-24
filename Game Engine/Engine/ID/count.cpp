//
//  count.cpp
//  Game Engine
//
//  Created by Indi Kernick on 11/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "count.hpp"

ID::Type ID::Count::create() {
  ids.insert(++count);
  return count;
}

void ID::Count::remove(Type id) {
  ids.erase(id);
}

void ID::Count::removeAll() {
  ids.clear();
}

bool ID::Count::has(Type id) {
  return ids.count(id);
}
