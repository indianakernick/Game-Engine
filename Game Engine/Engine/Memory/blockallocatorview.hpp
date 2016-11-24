//
//  blockallocatorview.hpp
//  Game Engine
//
//  Created by Indi Kernick on 7/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef blockallocatorview_hpp
#define blockallocatorview_hpp

#include "blockallocator.hpp"
#include <new>

namespace Memory {
  template <typename T>
  class BlockAllocatorView {
  public:
    BlockAllocatorView(BlockAllocator &allocator)
      : allocator(allocator) {
      assert(allocator.getItemSize() >= sizeof(T));
    }
    BlockAllocatorView(size_t blocksNum, size_t itemsNum = 1)
      : allocator(blocksNum, sizeof(T), itemsNum) {}
    
    template <typename ...ARGS>
    T *alloc(ARGS ...args) {
      return new (allocator.alloc()) T(std::forward<ARGS>(args)...);
    }
    void free(T *ptr) {
      //call destructor
      ptr->~T();
      allocator.free(ptr);
    }
    template <typename ...ARGS>
    T *allocArray(size_t size, ARGS ...args) {
      T *ptr = reinterpret_cast<T *>(allocator.allocArray(size));
      if (std::is_scalar<T>::value && sizeof...(ARGS) == 0) {
        return ptr;
      } else {
        for (T *i = ptr; i < ptr + size; i++) {
          new (i) T(std::forward<ARGS>(args)...);
        }
      }
    }
    void freeArray(T *ptr) {
      T *end = ptr + allocator.sizeOfArray(ptr);
      for (T *i = ptr; i < end; i++) {
        i->~T();
      }
      allocator.freeArray(ptr);
    }
  private:
    BlockAllocator allocator;
  };
}

#include "debugmacros.hpp"

#ifdef DEBUG
#include <map>

namespace Memory {
  struct AllocInfo {
    const char *file;
    int line;
  };
  using FreeInfo = AllocInfo;
  
  extern std::map<void *, AllocInfo> allocInfo;
  extern std::map<void *, FreeInfo> freeInfo;
  
  template <typename T, typename ...ARGS>
  T *safeAlloc(BlockAllocatorView<T> &allocator, const char *file, int line, ARGS ...args) {
    T *ptr = allocator.alloc(std::forward<ARGS>(args)...);
    auto iter = allocInfo.find(ptr);
    if (iter != allocInfo.end()) {
      std::cerr << "Allocating memory that was already allocated in file " << iter->second.file << " on line " << iter->second.line << '\n';
    }
    freeInfo.erase(ptr);
    allocInfo[ptr] = {file, line};
    return ptr;
  }
  
  template <typename T>
  void safeFree(BlockAllocatorView<T> &allocator, T *ptr, const char *file, int line) {
    auto iter = allocInfo.find(ptr);
    if (iter == allocInfo.end()) {
      auto iter = freeInfo.find(ptr);
      if (iter == freeInfo.end()) {
        std::cerr << "Deallocating memory that was already deallocated in file " << iter->second.file << " on line" << iter->second.line << '\n';
      } else {
        std::cerr << "Deallocating memory that was never allocated\n";
      }
    } else {
      allocInfo.erase(iter);
      freeInfo[ptr] = {file, line};
    }
    allocator.free(ptr);
  }
  
  template <typename T, typename ...ARGS>
  T *safeAllocArray(BlockAllocatorView<T> &allocator, const char *file, int line, ARGS ...args) {
    T *ptr = allocator.allocArray(std::forward<ARGS>(args)...);
    auto iter = allocInfo.find(ptr);
    if (iter != allocInfo.end()) {
      std::cerr << "Allocating memory that was already allocated in file " << iter->second.file << " on line " << iter->second.line << '\n';
    }
    freeInfo.erase(ptr);
    allocInfo[ptr] = {file, line};
    return ptr;
  }
  
  template <typename T>
  void safeFreeArray(BlockAllocatorView<T> &allocator, T *ptr, const char *file, int line) {
    auto iter = allocInfo.find(ptr);
    if (iter == allocInfo.end()) {
      auto iter = freeInfo.find(ptr);
      if (iter == freeInfo.end()) {
        std::cerr << "Deallocating memory that was already deallocated in file " << iter->second.file << " on line" << iter->second.line << '\n';
      } else {
        std::cerr << "Deallocating memory that was never allocated\n";
      }
    } else {
      allocInfo.erase(iter);
      freeInfo[ptr] = {file, line};
    }
    allocator.freeArray(ptr);
  }
  
  void checkSafety();
}

#define SAFE_ALLOC(allocator, args...) Memory::safeAlloc(allocator, __FILE__, __LINE__, args)
#define SAFE_ALLOC_DEF(allocator) Memory::safeAlloc(allocator, __FILE__, __LINE__)
#define SAFE_FREE(allocator, ptr) Memory::safeFree(allocator, ptr, __FILE__, __LINE__)

#define SAFE_ALLOC_ARRAY(allocator, args...) Memory::safeAllocArray(allocator, __FILE__, __LINE__, args)
#define SAFE_ALLOC_ARRAY_DEF(allocator) Memory::safeAllocArray(allocator, __FILE__, __LINE__)
#define SAFE_FREE_ARRAT(allocator, ptr) Memory::safeFreeArray(allocator, ptr, __FILE__, __LINE__)

#endif

#endif
