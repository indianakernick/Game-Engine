//
//  stackallocator.cpp
//  game engine
//
//  Created by Indi Kernick on 9/11/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "stackallocator.hpp"

#ifdef DEBUG

Buffer::StackAllocator::StackAllocator(size_t size, Overflow overflow)
  : memory(size),
    top(memory.begin()),
    overflow(overflow) {}

void *Buffer::StackAllocator::alloc(size_t size) {
  if (top + size >= memory.end()) {
    switch (overflow) {
      case THROW:
        throw std::runtime_error("Out of memory");
    }
  }
}

#else

Buffer::StackAllocator::StackAllocator(size_t size)
  : memory(size),
    top(memory.begin()) {}

#endif