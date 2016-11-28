//
//  int128.hpp
//  Game Engine
//
//  Created by Indi Kernick on 28/11/16.
//  Copyright © 2016 Indi Kernick. All rights reserved.
//

#ifndef int128_hpp
#define int128_hpp

#if __SIZEOF_INT128__ == 16
using int128_t = __int128;
using uint128_t = unsigned __int128;

#define __INT128_TYPE__
#define __UINT128_TYPE__
#endif

#ifdef __INT128_TYPE__

#include <cctype>

int128_t pow(int128_t b, int128_t e) {
  if (e < 0) {
    return 0;
  } else {
    int128_t out = 1;
    while (e--) {
      out *= b;
    }
    return out;
  }
}

uint128_t pow(uint128_t b, uint128_t e) {
  uint128_t out = 1;
  while (e--) {
    out *= b;
  }
  return out;
}

int128_t operator""_i128(const char *str, size_t size) {
  int128_t out = 0;
  
  bool neg = false;
  for (size_t i = 0; i < size; i++) {
    if (i == 0) {
      if (str[i] == '-') {
        if (neg) {
          throw std::runtime_error("Invalid literal");
        } else {
          neg = true;
        }
      }
    } else {
      if (isdigit(str[i])) {
        int128_t placeValue = str[i] - '0';
        int128_t place = size - i - 1;
        out += placeValue * pow(10, place);
      } else if (str[i] == ',' || str[i] == '\'') {
        continue;
      } else {
        throw std::runtime_error("Invalid literal");
      }
    }
  }
  
  if (neg) {
    return -out;
  } else {
    return out;
  }
}

uint128_t operator""_u128(const char *str, size_t size) {
  uint128_t out = 0;
  
  for (size_t i = 0; i < size; i++) {
    if (isdigit(str[i])) {
      uint128_t placeValue = str[i] - '0';
      uint128_t place = size - i - 1;
      out += placeValue * pow(10, place);
    } else if (str[i] == ',' || str[i] == '\'') {
      continue;
    } else {
      throw std::runtime_error("Invalid literal");
    }
  }
  
  return out;
}

#define INT128_MAX "340282366920938463463374607431768211456"_i128
#define UINT128_MAX "170141183460469231731687303715884105727"_u128

#endif

#endif
