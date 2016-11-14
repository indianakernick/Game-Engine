//
//  uuid.cpp
//  game engine
//
//  Created by Indi Kernick on 11/08/2016.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#include "uuid.hpp"

using namespace std;

random_device ID::UUID::gen;
uniform_int_distribution<uint64_t> ID::UUID::dist(0, __UINT64_MAX__);
const uint64_t ID::UUID::clearHi = 0xFFFFFFFFFFFF0FFF;
const uint64_t ID::UUID::clearLo = 0x0FFFFFFFFFFFFFFF;
const uint64_t ID::UUID::varient = 0x0000000000004000;
const uint64_t ID::UUID::reserve = 0x8000000000000000;

ID::UUID::UUID() {
  hi = (dist(gen) & clearHi) | varient;
  lo = (dist(gen) & clearLo) | reserve;
}

ID::UUID::UUID(string str)
  : hi(0), lo(0) {
  
  if (str.size() == 36) {
    static const uint8_t sizes[5] = {8,4,4,4,12};
    static const char chars[16] = {
      '0','1','2','3',
      '4','5','6','7',
      '8','9','a','b',
      'c','d','e','f'
    };
    uint8_t part = 0;
    uint8_t count = 0;
    uint8_t bitCount = 0;
    bool validChar;
    uint8_t charIndex = 0;
    
    for (uint8_t i = 0; i < 36; i++) {
      
      if (str[i] == '-') {
        if (sizes[part] != count) {
          throw invalid_argument("The input string must be a valid UUID string");
        }
        part++;
        count = 0;
        continue;
      }
      
      validChar = false;
      for (uint8_t j = 0; j < 16; j++) {
        if (str[i] == chars[j]) {
          validChar = true;
          charIndex = j;
          break;
        }
      }
      
      if (!validChar) {
        throw invalid_argument("The input string must be a valid UUID string");
      }
      
      if (bitCount < 16) {
        hi |= (static_cast<uint64_t>(charIndex) << ((31 - bitCount) * 4));
      } else {
        lo |= (static_cast<uint64_t>(charIndex) << ((31 - bitCount) * 4));
      }
      
      bitCount++;
      count++;
    }
  } else {
    throw invalid_argument("The input string must be a valid UUID string");
  }
}

ID::UUID::UUID(nullptr_t)
  : hi(0), lo(0) {}

bool ID::UUID::operator==(const UUID& other) {
  return lo == other.lo && hi == other.hi;
}

bool ID::UUID::operator!=(const UUID& other) {
  return lo != other.lo || hi != other.hi;
}

string ID::UUID::display() {
  string out;
  static const uint8_t sizes[5] = {8,4,4,4,12};
  static const char chars[16] = {
    '0','1','2','3',
    '4','5','6','7',
    '8','9','a','b',
    'c','d','e','f'
  };
  uint8_t part = 4;
  uint8_t count = 0;
  uint64_t source = lo;
  for (uint8_t i = 0; i < 32; i++) {
    if (i == 16)
      source = hi;
    out = chars[(source >> (i << 2)) & 15] + out;
    
    count++;
    if (count == sizes[part] && i != 31) {
      count = 0;
      part--;
      out = '-' + out;
    }
  }
  
  return out;
}