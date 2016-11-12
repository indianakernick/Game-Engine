//
//  blockallocator.cpp
//  game engine
//
//  Created by Indi Kernick on 7/10/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "blockallocator.hpp"

#ifdef DEBUG

const uint32_t Buffer::BlockAllocator::PATTERN = 0xDEADBEEF;
Byte Buffer::BlockAllocator::REPEATED_PATTERN[PADDING_SIZE];
bool Buffer::BlockAllocator::repeatedPatternFilled = false;

Buffer::BlockAllocator::BlockAllocator(size_t blocksNum, size_t itemSize, size_t itemsNum)
  : ITEM_SIZE(itemSize),
    ITEMS_NUM(itemsNum),
    MAX_ALLOC_SIZE(Math::max(ITEM_SIZE * ITEMS_NUM, MIN_ALLOC_SIZE)),
    BLOCK_SIZE(MAX_ALLOC_SIZE + PADDING_SIZE * 2),
    BLOCKS_NUM(blocksNum),
    freeBlocksNum(BLOCKS_NUM),
    memory(BLOCK_SIZE * BLOCKS_NUM),
    head(memory.begin() + PADDING_SIZE),
    arraySizes(BLOCKS_NUM, 0) {
  if (ITEM_SIZE * ITEMS_NUM < MIN_ALLOC_SIZE) {
    std::cerr << "Alloc size (" << (ITEM_SIZE * ITEMS_NUM) << ") is too small. Using minimum ("
      << MIN_ALLOC_SIZE << ") instead" << std::endl;
  }
  if (BLOCKS_NUM == 0) {
    throw std::runtime_error("Must allocate at least one block");
  }
  if (ITEMS_NUM == 0) {
    throw std::runtime_error("Must allocate at least one item per block");
  }
  
  if (!repeatedPatternFilled) {
    memset_pattern4(REPEATED_PATTERN, &PATTERN, PADDING_SIZE);
    repeatedPatternFilled = true;
  }
  
  for (Byte *i = memory.begin() + PADDING_SIZE; i < memory.end(); i+=BLOCK_SIZE) {
    memcpy(i - PADDING_SIZE, REPEATED_PATTERN, PADDING_SIZE);
    assign(i, i + BLOCK_SIZE);
    memcpy(i + MAX_ALLOC_SIZE, REPEATED_PATTERN, PADDING_SIZE);
  }
  assign(memory.end() - PADDING_SIZE - MAX_ALLOC_SIZE, nullptr);
}


Buffer::BlockAllocator::~BlockAllocator() {
  //if the allocator is destroyed before the blocks are freed then
  //the user will have pointers to deallocated memory
  if (freeBlocksNum < BLOCKS_NUM) {
    throw std::runtime_error("Allocator was destroyed before all blocks were freed");
  }
}

void Buffer::BlockAllocator::dumpMemory(std::ostream &stream, bool format) {
  if (format) {
    for (Byte *i = memory.begin(); i < memory.end();) {
      i += PADDING_SIZE;
      size_t index = blockIndex(i),
             arraySize = sizeOfArray(i),
             allocSize = sizeOfAlloc(i),
             restSize = sizeOfRest(i);
      i -= PADDING_SIZE;
      
      stream << "  Block Number     " << index << '\n';
      stream << "  Array Size       " << arraySize << '\n';
      stream << "  Allocation size  " << allocSize << '\n';
      stream << "  Rest size        " << restSize << '\n';
      stream << "Before padding\n";
      
      formatMemory(stream, i, PADDING_SIZE);
      i += PADDING_SIZE;
      
      stream << "\n"
                "End before padding\n"
                "Begin Raw data\n";
      
      stream.write(reinterpret_cast<char *>(i), allocSize);
      i += allocSize;
      
      stream << "\n"
                "End Raw data\n"
                "Begin rest\n";
      
      formatMemory(stream, i, restSize);
      i += restSize;
      
      stream << "\n"
                "End rest\n"
                "After padding\n";
      
      formatMemory(stream, i, PADDING_SIZE);
      i += PADDING_SIZE;
      
      stream << "\n"
                "End after padding\n"
                "\n";
      
    }
  } else {
    stream.write(reinterpret_cast<char *>(memory.begin()), memory.size());
  }
}

void *Buffer::BlockAllocator::alloc() {
  if (!head) {
    throw std::runtime_error("Out of memory");
  }
  freeBlocksNum--;
  Byte *out = head;
  head = deref<Byte *>(head);
  setSizeOfArray(out, 1);
  if (ITEMS_NUM > 1 || ITEM_SIZE < MIN_ALLOC_SIZE) {
    memset_pattern4(out + ITEM_SIZE, &PATTERN, MAX_ALLOC_SIZE - ITEM_SIZE);
  }
  
  return out;
}

void Buffer::BlockAllocator::free(void *ptr) {
  //this function is kind of funny becuase it will succeed to free an array
  //if you don't check for that
  if (isArray(ptr)) {
    throw std::runtime_error("Freeing array with the scalar version of free");
  }
  freeArray(ptr);
}

void *Buffer::BlockAllocator::allocArray(size_t size) {
  if (size > ITEMS_NUM) {
    throw std::runtime_error("Cannot allocate array greater than maximum size");
  }
  void *out = alloc();
  setSizeOfArray(out, size);
  return out;
}

void Buffer::BlockAllocator::freeArray(void *ptr) {
  if (!isWithinPool(ptr)) {
    throw std::range_error("Pointer out of range");
  }
  if (!isAligned(ptr)) {
    throw std::runtime_error("Pointer not aligned with BLOCK_SIZE");
  }
  
  if (!isAlloc(ptr)) {
    throw std::runtime_error("freeing memory that was not allocated");
  }
  
  if (paddingModified(ptr)) {
    throw std::runtime_error("Memory outside of block was modified");
  }
  if (restModified(ptr)) {
    throw std::runtime_error("Memory outside of allocated part of block was modified");
  }
  
  freeBlocksNum++;
  *reinterpret_cast<Byte **>(ptr) = head;
  head = reinterpret_cast<Byte *>(ptr);
}

bool Buffer::BlockAllocator::isAligned(void *ptr) const {
  return (toByte(ptr) - memory.begin()) % BLOCK_SIZE == PADDING_SIZE;
}

size_t Buffer::BlockAllocator::sizeOfArray(void *ptr) const {
  return arraySizes[blockIndex(ptr)];
}

size_t Buffer::BlockAllocator::blockIndex(void *ptr) const {
  if (!isValid(ptr)) {
    throw std::runtime_error("Invalid pointer");
  }
  return (toByte(ptr) - memory.begin()) / BLOCK_SIZE;
}

bool Buffer::BlockAllocator::beforePaddingModified(void *ptr) {
  if (memcmp(toByte(ptr) - PADDING_SIZE, REPEATED_PATTERN, PADDING_SIZE)) {
    memcpy(toByte(ptr) - PADDING_SIZE, REPEATED_PATTERN, PADDING_SIZE);
    std::cout << "left padding modified\n";
    return true;
  } else {
    return false;
  }
}

bool Buffer::BlockAllocator::afterPaddingModified(void *ptr) {
  if (memcmp(toByte(ptr) + MAX_ALLOC_SIZE, REPEATED_PATTERN, PADDING_SIZE)) {
    memcpy(toByte(ptr) + MAX_ALLOC_SIZE, REPEATED_PATTERN, PADDING_SIZE);
    std::cout << "right padding modified\n";
    return true;
  } else {
    return false;
  }
}

bool Buffer::BlockAllocator::paddingModified(void *ptr) {
  //have to call both of them no matter what
  bool modifed = false;
  modifed |= beforePaddingModified(ptr);
  modifed |= afterPaddingModified(ptr);
  return modifed;
}

bool Buffer::BlockAllocator::restModified(void *ptr) {
  const uint8_t *splitPattern = reinterpret_cast<const uint8_t *>(&PATTERN);
  Byte *start = toByte(ptr) + sizeOfAlloc(ptr);
  size_t end = sizeOfRest(ptr);
  for (size_t i = 0; i < end; i++) {
    if (start[i] != splitPattern[i % 4]) {
      return true;
    }
  }
  return false;
}

void Buffer::BlockAllocator::setSizeOfArray(void *ptr, size_t newSize) {
  arraySizes[blockIndex(ptr)] = newSize;
}

void Buffer::BlockAllocator::formatMemory(std::ostream &stream, Byte *ptr, size_t size) {
  //the memory has to read in 4 byte chunks becuase most machines are little
  //endian so i read it in 1 byte chunks it won't spell out DEADBEEF
  //4 byte chunks  DEADBEEF
  //2 byte chunks  BEEFDEAD
  //1 byte chunks  EFBEADDE
  ptrdiff_t trailingBytes = size % 4;
  uint32_t *end = reinterpret_cast<uint32_t *>(ptr + size - trailingBytes);
  for (uint32_t *i = reinterpret_cast<uint32_t *>(ptr); i < end; i++) {
    stream << Math::Format::hexPad32(*i);
  }
  if (trailingBytes) {
    uint32_t trail;
    memcpy(&trail, end, trailingBytes);
    stream << Math::Format::hexPad32(trail);
  }
}

#else // DEBUG is not defined

Buffer::BlockAllocator::BlockAllocator(size_t blocksNum, size_t itemSize, size_t itemsNum)
  : ITEM_SIZE(itemSize),
    ITEMS_NUM(itemsNum),
    MAX_ALLOC_SIZE(Math::max(ITEM_SIZE * ITEMS_NUM, MIN_ALLOC_SIZE)),
    BLOCK_SIZE(MAX_ALLOC_SIZE),
    BLOCKS_NUM(blocksNum),
    freeBlocksNum(BLOCKS_NUM),
    memory(BLOCK_SIZE * BLOCKS_NUM),
    head(memory.begin()),
    arraySizes(BLOCKS_NUM, 0) {
  Byte *last = memory.end() - MAX_ALLOC_SIZE;
  for (Byte *i = memory.begin(); i < last; i+=BLOCK_SIZE) {
    assign(i, i + BLOCK_SIZE);
  }
  assign(last, nullptr);
}

bool Buffer::BlockAllocator::isAligned(void *ptr) const {
  return (toByte(ptr) - memory.begin()) % BLOCK_SIZE == 0;
}

#endif

bool Buffer::BlockAllocator::isValid(void *ptr) const {
  return isAligned(ptr) && isWithinPool(ptr);
}

bool Buffer::BlockAllocator::isWithinPool(void *ptr) const {
  return ptr >= memory.begin() && ptr < memory.end();
}

bool Buffer::BlockAllocator::isArray(void *ptr) const {
  return sizeOfArray(ptr) > 1;
}

bool Buffer::BlockAllocator::isAlloc(void *ptr) const {
  return sizeOfArray(ptr);
}

size_t Buffer::BlockAllocator::sizeOfAlloc(void *ptr) const {
  return sizeOfArray(ptr) * ITEM_SIZE;
}

size_t Buffer::BlockAllocator::sizeOfRest(void *ptr) const {
  return MAX_ALLOC_SIZE - sizeOfAlloc(ptr);
}

size_t Buffer::BlockAllocator::getBlocksNum() const {
  return BLOCKS_NUM;
}

size_t Buffer::BlockAllocator::getItemSize() const {
  return ITEM_SIZE;
}

size_t Buffer::BlockAllocator::getItemsNum() const {
  return ITEMS_NUM;
}

size_t Buffer::BlockAllocator::getMaxAllocSize() const {
  return MAX_ALLOC_SIZE;
}

size_t Buffer::BlockAllocator::getBlockSize() const {
  return BLOCK_SIZE;
}

size_t Buffer::BlockAllocator::getFreeBlocks() const {
  return freeBlocksNum;
}