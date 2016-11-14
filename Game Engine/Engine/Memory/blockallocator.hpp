//
//  blockallocator.hpp
//  game engine
//
//  Created by Indi Kernick on 7/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef blockallocator_hpp
#define blockallocator_hpp

//originally i had the debug and release version mangled into one with
//ifdef DEBUG all over the place so i decided to separate them completly
//there is a bit a duplicate code but i think thats a fair price for
//organised code

#ifdef DEBUG

#include "raw.hpp"
#include "view.hpp"
#include "../Math/clamp.hpp"
#include <iostream>
#include "../Math/format.hpp"
#include "exceptions.hpp"

namespace Memory {
  class BlockAllocator {
  public:
    static const size_t MIN_ALLOC_SIZE = sizeof(Byte *);
    ///Number of padding bytes that will be allocated before and after the actual
    ///data to detect access into unallocated memory
    static const size_t PADDING_SIZE = 16;
    ///The pattern that will fill the padding and rest areas
    static const uint32_t PATTERN;
    ///blocksNum is the number of blocks available. itemSize is the size of the
    ///items that can be stored and itemsNum is the number of items that can be
    ///stored in each block
    BlockAllocator(size_t blocksNum, size_t itemSize, size_t itemsNum = 1);
    ~BlockAllocator();
    
    void dumpMemory(std::ostream &, bool format = true);
    
    void *alloc();
    void free(void *);
    
    void *allocArray(size_t size);
    void freeArray(void *);
    
    bool isValid(void *) const;
    bool isAligned(void *) const;
    bool isWithinPool(void *) const;
    bool isArray(void *) const;
    bool isAlloc(void *) const;
    
    size_t sizeOfArray(void *) const;
    ///The order of the block
    size_t blockIndex(void *) const;
    ///The size of the allocation
    size_t sizeOfAlloc(void *) const;
    ///The size of the part of the block not occupied by the allocation
    size_t sizeOfRest(void *) const;
    
    bool beforePaddingModified(void *);
    bool afterPaddingModified(void *);
    ///The padding bytes on the outside of the block have not been changed
    bool paddingModified(void *);
    ///The bytes in the block that are not in use have not been changed
    bool restModified(void *);
    
    size_t getItemSize() const;
    size_t getItemsNum() const;
    size_t getMaxAllocSize() const;
    size_t getBlockSize() const;
    size_t getBlocksNum() const;
    size_t getFreeBlocks() const;
  private:
    const size_t ITEM_SIZE;
    const size_t ITEMS_NUM;
    const size_t MAX_ALLOC_SIZE;
    const size_t BLOCK_SIZE;
    const size_t BLOCKS_NUM;
    size_t freeBlocksNum;
    
    Raw memory;
    Byte *head;
    PrimView<size_t> arraySizes;
    
    void setSizeOfArray(void *, size_t);
    
    //a helper used by dump memory to print some memory in 4 byte hex chunks
    static void formatMemory(std::ostream &, Byte *, size_t);
    
    //Some memory with the pattern repeated
    static Byte REPEATED_PATTERN[PADDING_SIZE];
    static bool repeatedPatternFilled;
  };
};

#else

#include "raw.hpp"
#include "view.hpp"
#include "../Math/clamp.hpp"

namespace Memory {
  class BlockAllocator {
  public:
    static const size_t MIN_ALLOC_SIZE = sizeof(Byte *);
    ///blocksNum is the number of blocks available. itemSize is the size of the
    ///items that can be stored and itemsNum is the number of items that can be
    ///store in each block
    BlockAllocator(size_t blocksNum, size_t itemSize, size_t itemsNum = 1);
    ~BlockAllocator() = default;
    
    inline void *alloc() {
      --freeBlocksNum;
      Byte *out = head;
      arraySizes[blockIndex(out)] = 1;
      head = *reinterpret_cast<Byte **>(head);
      return out;
    }
    inline void free(void *ptr) {
      arraySizes[blockIndex(ptr)] = 0;
      ++freeBlocksNum;
      *reinterpret_cast<Byte **>(ptr) = head;
      head = reinterpret_cast<Byte *>(ptr);
    }
    
    inline void *allocArray(size_t size) {
      --freeBlocksNum;
      Byte *out = head;
      arraySizes[blockIndex(out)] = size;
      head = *reinterpret_cast<Byte **>(head);
      return out;
    }
    inline void freeArray(void *ptr) {
      free(ptr);
    }
    
    bool isValid(void *) const;
    bool isAligned(void *) const;
    bool isWithinPool(void *) const;
    bool isArray(void *) const;
    bool isAlloc(void *) const;
    
    size_t sizeOfArray(void *ptr) const {
      return arraySizes[blockIndex(ptr)];
    }
    ///The order of the block
    inline size_t blockIndex(void *ptr) const {
      return (reinterpret_cast<Byte *>(ptr) - memory.begin()) / BLOCK_SIZE;
    }
    ///The size of the allocation
    size_t sizeOfAlloc(void *) const;
    ///The size of the part of the block not occupied by the allocation
    size_t sizeOfRest(void *) const;
    
    size_t getItemSize() const;
    size_t getItemsNum() const;
    size_t getMaxAllocSize() const;
    size_t getBlockSize() const;
    size_t getBlocksNum() const;
    size_t getFreeBlocks() const;
  private:
    const size_t ITEM_SIZE;
    const size_t ITEMS_NUM;
    const size_t MAX_ALLOC_SIZE;
    const size_t BLOCK_SIZE;
    const size_t BLOCKS_NUM;
    size_t freeBlocksNum;
    
    Raw memory;
    Byte *head;
    PrimView<size_t> arraySizes;
  };
};

#endif // DEBUG

#endif
