//
//  buffer.hpp
//  Game Engine
//
//  Created by Indi Kernick on 25/09/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef engine_memory_raw_hpp
#define engine_memory_raw_hpp

#include <cstddef>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <math.h>
#include <memory>
#include "byteptr.hpp"

namespace Memory {
  enum Assign : Byte {
    ///The new memory will be copied into the existing buffer
    COPY,
    ///The new memory will be owned by the Buffer object
    MOVE,
    ///The new memory will be accessable with the Buffer object but is not
    ///owned by the Buffer object so it will not deallocate the memory
    ALIAS
  };

  class Buffer {
  public:
    explicit Buffer(const size_t);
    ///The pointer should point to memory allocated with operator new
    Buffer(void *, const size_t, Assign = MOVE);
    Buffer(const size_t, const uint8_t);
    Buffer(const size_t, const uint16_t);
    Buffer(const size_t, const uint32_t);
    Buffer(const size_t, const uint64_t);
    Buffer(const Buffer &) = default;
    Buffer(Buffer &&) = default;
    ~Buffer() = default;
    
    Buffer& operator=(const Buffer &) = default;
    Buffer& operator=(Buffer &&) = default;
    
    bool operator==(const Buffer &) const;
    bool operator!=(const Buffer &) const;
    
    void fill(const uint8_t  chunk, size_t start = 0, size_t dist = 0);
    void fill(const uint16_t chunk, size_t start = 0, size_t dist = 0);
    void fill(const uint32_t chunk, size_t start = 0, size_t dist = 0);
    void fill(const uint64_t chunk, size_t start = 0, size_t dist = 0);
    void fill(const uint64_t chunk[2], size_t start = 0, size_t dist = 0);
    void fill(const void *chunk, size_t chunkSize, size_t start = 0, size_t dist = 0);
    
    static const size_t NOT_FOUND = __UINTMAX_MAX__;//or i could just type -1
    
    size_t find(const Byte    ,                        size_t start = 0, size_t dist = 0) const;
    size_t find(const Buffer &, size_t otherStart = 0, size_t start = 0, size_t dist = 0) const;
    size_t find(void *        , size_t otherSize     , size_t start = 0, size_t dist = 0) const;
    
    void copy(const Buffer &other);
    void copy(const void *, const size_t);
    ///The pointer should point to memory allocated with operator new
    void move(const void *, const size_t);
    
    ///Copy a part of this Buffer to another Buffer
    void copyTo(Buffer& other, size_t otherI, size_t thisI, size_t size) const;
    ///Copy a part of this Buffer to another Buffer
    void copyTo(void *other, size_t thisI, size_t size) const;
    
    ///Copy a part of this Buffer to another part of this Buffer
    void copyWithin(size_t srcStart, size_t dstStart, size_t dist);
    
    ///Swap Buffers by exchanging pointers
    static void swap(Buffer &, Buffer &);
    
    inline size_t size() const {
      return mSize;
    }
    void resize(size_t newSize, bool copy = false);
    
    inline const Byte *add(const size_t i) const {
      assert(i < mSize);
      return begin() + i;
    }
    inline Byte *add(const size_t i) {
      assert(i < mSize);
      return begin() + i;
    }
    
    inline size_t index(Byte *pointer) const {
      assert(pointer >= begin());
      assert(pointer < end());
      
      return pointer - begin();
    }
    
    inline Byte *begin() {
      return mData.get();
    }
    inline Byte *end() {
      return begin() + mSize;
    }
    inline const Byte *begin() const {
      return mData.get();
    }
    inline const Byte *end() const {
      return begin() + mSize;
    }
    
    //because i can't decide between c and c++
    static inline Byte *alloc(size_t size) {
      return static_cast<Byte *>(operator new(size));
    }
    static inline void free(Byte *data) {
      operator delete(data);
    }
    static inline Byte *resize(Byte *data, size_t newSize) {
      free(data);
      return alloc(newSize);
    }
  private:
    std::shared_ptr<Byte> mData = nullptr;
    size_t mSize = 0;
    inline size_t getDist(size_t start, size_t dist) const {
      return dist == 0 ?  mSize - start : dist;
    }
    static std::shared_ptr<Byte> makePtr(Byte *);
  };
}

#endif
