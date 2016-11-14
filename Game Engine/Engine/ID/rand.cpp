//
//  rand.cpp
//  game engine
//
//  Created by Indi Kernick on 11/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "rand.hpp"

ID::Type ID::Rand::create() {
  Type id;
  do {
    id = dist(gen);
  } while (ids.count(id));
  ids.insert(id);
  return id;
}

void ID::Rand::remove(Type id) {
  ids.erase(id);
}

void ID::Rand::removeAll() {
  ids.clear();
}

bool ID::Rand::has(Type id) {
  return ids.count(id);
}