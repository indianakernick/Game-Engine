//
//  buffer.cpp
//  Game Engine
//
//  Created by Indi Kernick on 25/09/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "buffer.hpp"

Memory::Buffer::Buffer(const size_t size)
  : mData(alloc(size), free), mSize(size) {
  assert(mData);
  assert(mSize);
}

Memory::Buffer::Buffer(void *data, const size_t size, Assign assign)
  : mData(assign == COPY ? alloc(size) : toByte(data),
          assign == ALIAS ? [](Byte*){} : free),
    mSize(size) {
  assert(mData);
  assert(mSize);
  if (assign == COPY) {
    copy(data, size);
  }
}

Memory::Buffer::Buffer(size_t size, const uint8_t chunk)
  : mData(alloc(size), free), mSize(size) {
  assert(mData);
  assert(mSize);
  fill(chunk);
}

Memory::Buffer::Buffer(size_t size, const uint16_t chunk)
  : mData(alloc(size), free), mSize(size) {
  assert(mData);
  assert(mSize);
  fill(chunk);
}

Memory::Buffer::Buffer(size_t size, const uint32_t chunk)
  : mData(alloc(size), free), mSize(size) {
  assert(mData);
  assert(mSize);
  fill(chunk);
}

Memory::Buffer::Buffer(size_t size, const uint64_t chunk)
  : mData(alloc(size), free), mSize(size) {
  assert(mData);
  assert(mSize);
  fill(chunk);
}

bool Memory::Buffer::operator==(const Buffer &other) const {
  return mSize == other.mSize &&
         memcmp(mData.get(), other.mData.get(), mSize) == 0;
}

bool Memory::Buffer::operator!=(const Buffer &other) const {
  return mSize != other.mSize ||
         memcmp(mData.get(), other.mData.get(), mSize) != 0;
}

void Memory::Buffer::fill(const uint8_t chunk, size_t start, size_t dist) {
  assert(start + getDist(start, dist) <= mSize);
  memset(add(start), chunk, getDist(start, dist));
}

void Memory::Buffer::fill(const uint16_t chunk, size_t start, size_t dist) {
  assert(start + getDist(start, dist) <= mSize);
  //why isn't there a memset_pattern2 ?
  uint16_t chunk2[2] = {chunk, chunk};
  memset_pattern4(add(start), chunk2, getDist(start, dist));
}

void Memory::Buffer::fill(const uint32_t chunk, size_t start, size_t dist) {
  assert(start + getDist(start, dist) <= mSize);
  memset_pattern4(add(start), &chunk, getDist(start, dist));
}

void Memory::Buffer::fill(const uint64_t chunk, size_t start, size_t dist) {
  assert(start + getDist(start, dist) <= mSize);
  memset_pattern8(add(start), &chunk, getDist(start, dist));
}

void Memory::Buffer::fill(const uint64_t chunk[2], size_t start, size_t dist) {
  assert(start + getDist(start, dist) <= mSize);
  memset_pattern16(add(start), chunk, getDist(start, dist));
}

void Memory::Buffer::fill(const void *chunk, size_t chunkSize, size_t start, size_t dist) {
  assert(start + getDist(start, dist) <= mSize);
  switch (chunkSize) {
    case 1:
      fill(*reinterpret_cast<const uint8_t*>(chunk), start, dist);
      break;
    case 2:
      fill(*reinterpret_cast<const uint16_t*>(chunk), start, dist);
      break;
    case 4:
      fill(*reinterpret_cast<const uint32_t*>(chunk), start, dist);
      break;
    case 8:
      fill(*reinterpret_cast<const uint64_t*>(chunk), start, dist);
      break;
    case 16:
      //notice we don't dereference
      fill(reinterpret_cast<const uint64_t*>(chunk), start, dist);
      break;
    default: {
      //if dist is not a multiple of chunkSize then the end ptr will be after
      //the last full chunk
      Byte *endPtr = begin() + (end() - begin()) / chunkSize * chunkSize;
      for (Byte *i = begin(); i < endPtr; i += chunkSize) {
        memcpy(i, chunk, chunkSize);
      }
      memcpy(endPtr, chunk, end() - endPtr);
    }
  }
}

size_t Memory::Buffer::find(const uint8_t byte, size_t start, size_t dist) const {
  assert(start + (getDist(start, dist)) < mSize);
  Byte *out = toByte(memchr(add(start), byte, getDist(start, dist)));
  return out == nullptr ? NOT_FOUND : index(out);
}

size_t Memory::Buffer::find(const Buffer &other, size_t otherStart, size_t start, size_t dist) const {
  assert(other.mSize < mSize);
  Byte *out = toByte(memmem(add(start * otherStart),
                                getDist(start, dist),
                                other.add(otherStart),
                                other.mSize));
  return out == nullptr ? NOT_FOUND : index(out);
}

size_t Memory::Buffer::find(void *other, size_t otherSize, size_t start, size_t dist) const {
  Byte *out = toByte(memmem(add(start),
                         getDist(start, dist),
                         other,
                         otherSize));
  return out == nullptr ? NOT_FOUND : index(out);
}

void Memory::Buffer::copy(const Buffer &other) {
  if (mSize != other.mSize) {
    mData = makePtr(resize(mData.get(), other.mSize));
    mSize = other.mSize;
  }
  memcpy(mData.get(), other.mData.get(), mSize);
}

void Memory::Buffer::copy(const void *newData, size_t newSize) {
  if (mSize != newSize) {
    mData = makePtr(resize(mData.get(), newSize));
    mSize = newSize;
  }
  memcpy(mData.get(), newData, mSize);
}

void Memory::Buffer::move(const void *newData, size_t newSize) {
  free(mData.get());
  mData = makePtr(toByte(const_cast<void *>(newData)));
  mSize = newSize;
}

void Memory::Buffer::copyTo(Buffer &other, size_t dst, size_t src, size_t size) const {
  assert(dst + size < other.mSize);
  assert(src + size < mSize);
  memcpy(other.add(dst), add(src), size);
}

void Memory::Buffer::copyTo(void *other, size_t src, size_t size) const {
  assert(src + size < mSize);
  memcpy(other, add(src), size);
}

void Memory::Buffer::copyWithin(size_t src, size_t dst, size_t size) {
  assert(dst + size < mSize);
  assert(src + size < mSize);
  memmove(add(dst), add(src), size);
}

void Memory::Buffer::resize(size_t newSize, bool copy) {
  assert(newSize);
  if (copy) {
    std::shared_ptr<Byte> newData = makePtr(alloc(newSize));
    assert(newData);
    memcpy(newData.get(), mData.get(), newSize < mSize ? newSize : mSize);
    mData = newData;
    mSize = newSize;
  } else {
    mData = makePtr(resize(mData.get(), newSize));
    assert(mData);
    mSize = newSize;
  }
}

std::shared_ptr<Byte> Memory::Buffer::makePtr(Byte *ptr) {
  return std::shared_ptr<Byte>(ptr, free);
}
