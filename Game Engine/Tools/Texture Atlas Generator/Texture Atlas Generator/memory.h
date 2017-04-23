//
//  memory.h
//  Texture Atlas Generator
//
//  Created by Indi Kernick on 23/4/17.
//  Copyright © 2017 Indi Kernick. All rights reserved.
//

#ifndef memory_h
#define memory_h

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

void *allocate(size_t);
void deallocate(void *);
void *reallocate(void *, size_t);

#ifdef __cplusplus
}

template <typename T>
T *allocate(size_t size) {
  return reinterpret_cast<T *>(allocate(size));
}
#endif

#endif
