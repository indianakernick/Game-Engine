//
//  memory.cpp
//  Texture Atlas Generator
//
//  Created by Indi Kernick on 23/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#include "memory.h"

#include <cstdlib>

//I'm using malloc/free because realloc implemented in terms of operator new
//and operator delete is much slower than realloc

//this file is still written in c++ in case I decide to change my mind for
//whatever reason

void *allocate(size_t size) {
  return std::malloc(size);
}

void deallocate(void *ptr) {
  std::free(ptr);
}

void *reallocate(void *ptr, size_t size) {
  return std::realloc(ptr, size);
}
