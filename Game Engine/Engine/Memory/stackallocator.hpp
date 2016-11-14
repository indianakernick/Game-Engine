//
//  stackallocator.hpp
//  game engine
//
//  Created by Indi Kernick on 9/11/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef stackallocator_hpp
#define stackallocator_hpp

#ifdef DEBUG

#include "raw.hpp"
#include "primview.hpp"
#include <stdexcept>

namespace Memory {
  class StackAllocator {
  public:
    enum Overflow : char {
      THROW,
      REALLOC
    };
  
    StackAllocator(size_t size, Overflow = THROW);
    
    void *alloc(size_t size);
    void free(void *);
    
    void *allocArray(size_t itemSize, size_t arraySize);
    void freeArray(void *);
  private:
    Raw memory;
    Byte *top;
    const Overflow overflow;
  };
}

#else

#include "raw.hpp"

//The release version has no safety nets in place
//if you use it incorrectly, you'll get undefined behaviour

namespace Memory {
  class StackAllocator {
  public:
    StackAllocator(size_t size);
    
    inline void *alloc(size_t size) {
      void *out = top;
      top += size;
      return out;
    }
    inline void free(void *ptr) {
      top = reinterpret_cast<Byte *>(ptr);
    }
    
    inline void *allocArray(size_t itemSize, size_t arraySize) {
      void *out = top;
      top += itemSize * arraySize;
      return out;
    }
    inline void freeArray(void *ptr) {
      top = reinterpret_cast<Byte *>(ptr);
    }
  private:
    Raw memory;
    Byte *top;
  };
}

#endif

#endif
