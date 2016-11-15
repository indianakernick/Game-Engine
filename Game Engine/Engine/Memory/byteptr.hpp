//
//  byteptr.hpp
//  game engine
//
//  Created by Indi Kernick on 2/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef byteptr_hpp
#define byteptr_hpp

#include <cstdint>
#include <cstddef>
#include <new>
#include <type_traits>

using Byte = uint8_t;

namespace Memory {
  inline uintptr_t toNum(void *bytePtr) {
    return reinterpret_cast<uintptr_t>(bytePtr);
  }
  inline Byte *toByte(void *ptr) {
    return reinterpret_cast<Byte *>(ptr);
  }
  inline void *alignTo(void *ptr, size_t align) {
    uintptr_t outOfAlign = toNum(ptr) % align;
    // x % x == 0 so without the check we would waste memory when the ptr
    // is aligned
    return outOfAlign ? toByte(ptr) + (align - outOfAlign) : ptr;
  }
  template <typename T>
  inline void *alignFor(void *ptr) {
    return alignTo(ptr, alignof(T));
  }
  template <typename T>
  T& deref(Byte *bytePtr) {
    return *reinterpret_cast<T *>(bytePtr);
  }
  template <typename T>
  inline void assign(Byte *ptr, T &&value) {
    new (ptr) typename std::remove_reference<T>::type (std::forward<T>(value));
  }
  template <typename T>
  inline void assign(Byte *ptr, const T &value) {
    new (ptr) typename std::remove_reference<T>::type (std::forward<T>(value));
  }
}

#endif
